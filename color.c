#include "rtv1.h"

static double	shadow(t_list *list, t_obj *light, t_hit hit)
{
	double	t;
	t_vec	l;
	t_vec	ln;
	t_obj	*hit_obj;
	t_ray	ray;

	hit_obj = NULL;
	l = vec_sub(&light->pos, &hit.point);
	ln.x = l.x;
	ln.y = l.y;
	ln.z = l.z;
	normalize(&l);
	ray.origin = hit.point;
	ray.dir = l;
	t = find_closest_t(list, &ray, &hit_obj);
	if (hit_obj != NULL)
		hit_obj->current = 0;
	if (t > MIN && t < sqrtf(dot(&ln, &ln)))
		return (t);
	return (-1);
}

static double	get_spec(t_vec l, t_vec v, t_hit hit)
{
	t_vec	halfway;
	double	specular;

	halfway = vec_add(&l, &v);
	normalize(&halfway);
	specular = dot(&hit.normal, &halfway);
	specular = specular > MIN ? specular : 0.0;
	specular = pow(specular, 100);
	return (specular);
}

static t_color	set_color(t_obj *light, t_obj *obj,
		double specul, double cos_teta)
{
	t_color col;

	col.r = ((obj->color.r / 255.0) * obj->ambient +
			(light->color.r / 255.0) * obj->diffuse * cos_teta +
			(light->color.r / 255.0) * specul * obj->specular) * 255;
	col.g = ((obj->color.g / 255.0) * obj->ambient +
			(light->color.g / 255.0) * obj->diffuse * cos_teta +
			(light->color.g / 255.0) * specul * obj->specular) * 255;
	col.b = ((obj->color.b / 255.0) * obj->ambient +
			(light->color.b / 255.0) * obj->diffuse * cos_teta +
			(light->color.b / 255.0) * specul * obj->specular) * 255;
	return (col);
}

static t_color	get_hit_color(t_list *list, t_obj *light, t_obj *obj, t_hit hit)
{
	t_color	col;
	t_vec	v;
	t_vec	l;
	double	cos_teta;
	double	specular;

	l = vec_sub(&light->pos, &hit.point);
	v = vec_sub(&hit.ray_origin->origin, &hit.point);
	normalize(&v);
	normalize(&l);
	if (shadow(list, light, hit) != -1)
	{
		col.r = obj->color.r * obj->ambient;
		col.g = obj->color.g * obj->ambient;
		col.b = obj->color.b * obj->ambient;
		return (col);
	}
	cos_teta = ft_min_max(dot(&hit.normal, &l), 0, 1);
	specular = get_spec(l, v, hit);
	col = set_color(light, obj, specular, cos_teta);
	return (col);
}

t_color			lighting(t_list *list, t_obj **obj, t_ray ray, double t)
{
	t_list	*node;
	t_color	col;
	t_hit	hit;
	t_color	tmp_col;

	node = list;
	hit.t = t;
	col.r = 0;
	col.g = 0;
	col.b = 0;
	get_hit_point_info(&hit, *obj, &ray);
	while (node)
	{
		if (((t_obj*)node->content)->name == LIGHT)
		{
			tmp_col = get_hit_color(list, (t_obj*)node->content, *obj, hit);
			col.r = (col.r + tmp_col.r) > 255 ? 255 : col.r + tmp_col.r;
			col.g = (col.g + tmp_col.g) > 255 ? 255 : col.g + tmp_col.g;
			col.b = (col.b + tmp_col.b) > 255 ? 255 : col.b + tmp_col.b;
		}
		node = node->next;
	}
	return (col);
}