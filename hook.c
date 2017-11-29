/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilips <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:10:35 by gphilips          #+#    #+#             */
/*   Updated: 2017/11/29 17:27:27 by gphilips         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				key_hook(int key, t_env *e)
{
	if (key == ESC)
	{
		mlx_destroy_window(e->mlx.mlx, e->mlx.win);
		exit(0);
	}
	if (key == KEY_P && e->zoom <= 10)
		e->zoom++;
	if (key == KEY_L && e->zoom > 1)
		e->zoom--;
	if (key == KEY_PLUS)
	 	e->aa *= 2;
	if (key == KEY_MOINS)
	 	e->aa /= 2;
	 e->aa = (e->aa < 1) ? 1 : e->aa;
	// if (key == KEY_H)
	// 	e->help *= -1;
	// if (key == KEY_L)
	// {
	// 	e->l = (e->l == (e->total_light - 1) ? 0 : (e->l + 1));
	// 	e->hit_obj = e->light[e->l];
	// 	e->is_obj_selected = 1;
	// 	put_image(e);
	// 	return (0);
	// }
	// translate(key, e);
	// rotate(key, e);
	draw_screen(e);
	put_image(e);
	return (0);
}
