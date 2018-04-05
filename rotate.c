/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mushah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 12:51:48 by mushah            #+#    #+#             */
/*   Updated: 2018/04/05 18:48:31 by gphilips         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	rotate_rot(int key, t_vec *nml)
{
	if (key == KEY_PAD_1)
		*nml = (t_vec){nml->x * cosf(0.13) + nml->y *
			sinf(-0.13), nml->x * sinf(0.13) + nml->y * cosf(0.13), nml->z};
	if (key == KEY_PAD_2)
		*nml = (t_vec){nml->x * cosf(-0.13) + nml->y * sinf(0.13)
			, nml->x * sinf(-0.13) + nml->y * cosf(-0.13), nml->z};
	if (key == KEY_PAD_4)
		*nml = (t_vec){nml->x * cosf(0.13) + nml->z * sinf(0.13)
			, nml->y, nml->x * sinf(-0.13) + nml->z * cosf(0.13)};
	if (key == KEY_PAD_5)
		*nml = (t_vec){nml->x * cosf(-0.13) + nml->z *
			sinf(-0.13), nml->y, nml->x * sinf(0.13) + nml->z * cosf(-0.13)};
	if (key == KEY_PAD_7)
		*nml = (t_vec){nml->x, nml->y * cosf(0.13) + nml->z *
			sinf(-0.13), nml->y * sinf(0.13) + nml->z * cosf(0.13)};
	if (key == KEY_PAD_8)
		*nml = (t_vec){nml->x, nml->y * cosf(-0.13) + nml->z *
			sinf(0.13), nml->y * sinf(-0.13) + nml->z * cosf(-0.13)};
}

void		rotate(int key, t_env *e)
{
	if (e->is_obj_selected != 1)
	{
		rotate_rot(key, &e->cam.pos);
		rotate_rot(key, &e->cam.dir);
	}
	else
		rotate_rot(key, &e->hit_obj->normal);
}
