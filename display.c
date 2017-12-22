/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilips <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 18:10:52 by gphilips          #+#    #+#             */
/*   Updated: 2017/12/09 15:50:05 by gphilips         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			display_instruction(void)
{
	char 	*str[10];
	int		i;

	str[0] = "INSTRUCTIONS";
	str[1] = "-------------";
	str[2] = "Move : Arrows";
	str[3] = "Rotate : 1 | 2 | 4 | 5 | 7 | 8";
	str[4] = "Zoom : P | L";
	str[5] = "Color : 1 | 2 | 3";
	str[6] = "Anti-aliasing : + | -";
	str[7] = "Select object : Left click";
	str[8] = "Select light : Tab";
	str[9] = "Deselect : R";
	i = -1;
	while (str[++i])
		ft_putendl(str[i]);
}

static void		display_cam_info(t_env *e)
{
	char	*x;
	char	*y;
	char	*z;

	x = ft_itoa(e->cam.pos.x);
	y = ft_itoa(e->cam.pos.y);
	z = ft_itoa(e->cam.pos.z);
	mlx_string_put(e->mlx.mlx, e->mlx.win, 20, 120, 0x000000, x);
	mlx_string_put(e->mlx.mlx, e->mlx.win, 90, 120, 0x000000, y);
	mlx_string_put(e->mlx.mlx, e->mlx.win, 150, 120, 0x000000, z);
	ft_strdel(&x);
	ft_strdel(&y);
	ft_strdel(&z);
}

static void		display_obj_info(t_env *e)
{
	char	*x;
	char	*y;
	char	*z;

	x = ft_itoa(e->hit_obj->pos.x);
	y = ft_itoa(e->hit_obj->pos.y);
	z = ft_itoa(e->hit_obj->pos.z);
	mlx_string_put(e->mlx.mlx, e->mlx.win, 20, 280, 0x000000, x);
	mlx_string_put(e->mlx.mlx, e->mlx.win, 90, 280, 0x000000, y);
	mlx_string_put(e->mlx.mlx, e->mlx.win, 170, 280, 0x000000, z);
	ft_strdel(&x);
	ft_strdel(&y);
	ft_strdel(&z);
}

static void		display_clr_info(t_env *e)
{
	char	*r;
	char	*g;
	char	*b;

	r = ft_itoa(e->hit_obj->color.r);
	g = ft_itoa(e->hit_obj->color.g);
	b = ft_itoa(e->hit_obj->color.b);
	mlx_string_put(e->mlx.mlx, e->mlx.win, 20, 440, 0x000000, r);
	mlx_string_put(e->mlx.mlx, e->mlx.win, 90, 440, 0x000000, g);
	mlx_string_put(e->mlx.mlx, e->mlx.win, 150, 440, 0x000000, b);
	ft_strdel(&r);
	ft_strdel(&g);
	ft_strdel(&b);
}

void		display_info(t_env *e)
{
	display_cam_info(e);
	if (e->is_obj_selected == 1)
	{
		display_obj_info(e);
		display_clr_info(e);
	}
}
