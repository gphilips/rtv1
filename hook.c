/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilips <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:10:35 by gphilips          #+#    #+#             */
/*   Updated: 2017/12/09 15:54:51 by gphilips         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int 		quit(t_env *e)
{
	mlx_destroy_image(e->mlx.mlx, e->mlx.img);
	mlx_destroy_image(e->mlx.mlx, e->mlx.img_tex);
	mlx_destroy_window(e->mlx.mlx, e->mlx.win);
	exit(0);
	return (0);
}

int			clicked_obj(int x, int y, t_env *e)
{
	double		t;
	t_ray		ray;

	e->hit_obj = NULL;
	current_ray(x, y, e, &ray);
	t = find_closest_t(e->obj, &ray, &e->hit_obj);
	if (t > MIN && t < MAX && e->hit_obj)
	{
		e->hit_obj->current = 0;
		e->is_obj_selected = 1;
		return (1);
	}
	return (0);
}

int			mouse_hook(int button, int x, int y, t_env *e)
{
	if (button == 1 && x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		if (clicked_obj(x, y, e) == 1)
			put_image(e);
		else
		{
			free(e->hit_obj);
			e->hit_obj = NULL;
			e->is_obj_selected = 0;
		}
	}
	return (0);
}

void static	change_color(int key, t_obj *obj)
{
	if (key == KEY_1)
		obj->color.r = (obj->color.r > 255) ? 0 : obj->color.r + 10;
	else if (key == KEY_2)
		obj->color.g = (obj->color.g > 255) ? 0 : obj->color.g + 10;
	else
		obj->color.b = (obj->color.b > 255) ? 0 : obj->color.b + 10;
}

int			key_hook(int key, t_env *e)
{
	if (key == ESC)
		quit(e);
	if (key == KEY_PLUS)
	 	e->aa *= 2;
	if (key == KEY_MOINS)
	 	e->aa /= 2;
	 e->aa = (e->aa < 1) ? 1 : e->aa;
	// if (key == KEY_H)
	// 	e->help *= -1;
	if ((key == KEY_1 || key == KEY_2 || key == KEY_3)
		&& e->is_obj_selected == 1)
		change_color(key, e->hit_obj);
	if (key == KEY_TAB)
	{
		e->l = (e->l == (e->total_light - 1) ? 0 : (e->l + 1));
		e->hit_obj = e->light[e->l];
		e->is_obj_selected = 1;
	//	put_image(e);
	//	return (0);
	}
	translate(key, e);
	rotate(key, e);
	draw_screen(e);
	put_image(e);
	return (0);
}
