/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilips <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 18:10:52 by gphilips          #+#    #+#             */
/*   Updated: 2017/11/29 18:27:27 by gphilips         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	display_cam_info(t_env *e)
{
	mlx_string_put(e->mlx.mlx, e->mlx.win, 20, 120, 0x000000,
		ft_itoa(e->cam.pos.x));
	mlx_string_put(e->mlx.mlx, e->mlx.win, 90, 120, 0x000000,
		ft_itoa(e->cam.pos.y));
	mlx_string_put(e->mlx.mlx, e->mlx.win, 150, 120, 0x000000,
		ft_itoa(e->cam.pos.z));
}

void	display_info(t_env *e)
{
	display_cam_info(e);
}
