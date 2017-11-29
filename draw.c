#include "rtv1.h"

static void		put_pixel(t_mlx *mlx, int x, int y, t_color color)
{
	int		i;

	if ((x >= 0 && x < WIDTH) && (y >= 0 && y < HEIGHT))
	{
		i = (y * mlx->sl) + (x * mlx->bpp / 8);
		mlx->data[i] = color.b;
		mlx->data[i + 1] = color.g;
		mlx->data[i + 2] = color.r;
	}
}

static void		sum_color(double sum[3], t_color *c, double p, int flag)
{
	if (flag == INIT)
	{
		sum[0] = 0.0;
		sum[1] = 0.0;
		sum[2] = 0.0;
	}
	if (flag == ADD)
	{
		sum[0] += (double)c->r;
		sum[1] += (double)c->g;
		sum[2] += (double)c->b;
	}
	if (flag == SUM)
	{
		c->r = sum[0] / p;
		c->g = sum[1] / p;
		c->b = sum[2] / p;
	}
}

static void		check_t(t_env *env, double sum[3], t_ray ray, t_obj *hit_obj)
{
	t_color	color;

	if (env->t > MIN && env->t < MAX)
		color = lighting(env->obj, &hit_obj, ray, env->t);
	else
		color = (t_color){0, 0, 0};
	if (hit_obj)
		hit_obj->current = 0;
	sum_color(sum, &color, env->p, ADD);
}

static t_color	get_pixel_color(t_env *env, int x, int y)
{
	double	sub[2];
	t_ray	ray;
	t_obj	*hit_obj;
	double	sum[3];
	t_color	color;

	sub[1] = y;
	sum_color(sum, &color, env->p, INIT);
	env->p = 0.0;
	while (sub[1] < y + 1)
	{
		sub[0] = x;
		while (sub[0] < x + 1)
		{
			hit_obj = NULL;
			current_ray(sub[0], sub[1], env, &ray);
			env->t = find_closest_t(env->obj, &ray, &hit_obj);
			check_t(env, sum, ray, hit_obj);
			sub[0] += 1.0 / env->aa;
			env->p += 1;
		}
		sub[1] += 1.0 / env->aa;
	}
	sum_color(sum, &color, env->p, SUM);
	return (color);
}

void			draw_screen(t_env *e)
{
	int		x;
	int		y;
	t_color	color;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			color = get_pixel_color(e, x, y);
			put_pixel(&e->mlx, x, y, color);
		}
	}
}