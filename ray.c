/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilips <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:09:55 by gphilips          #+#    #+#             */
/*   Updated: 2017/11/29 17:09:57 by gphilips         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	current_ray(double x, double y, t_env *e, t_ray *ray)
{
	double	xindent;
	double	yindent;

	e->cam.normal = vec_sub(&e->cam.dir, &e->cam.pos);
	normalize(&e->cam.normal);
	e->cam.right = vec_cross(&e->cam.normal, &e->up);
	normalize(&e->cam.right);
	e->cam.up = vec_cross(&e->cam.right, &e->cam.normal);
	xindent = (WIDTH - x * 2.0) / HEIGHT;
	yindent = (HEIGHT - y * 2.0) / WIDTH;
	ray->origin.x = e->cam.pos.x;
	ray->origin.y = e->cam.pos.y;
	ray->origin.z = e->cam.pos.z;
	ray->dir.x = ZOOM * e->cam.normal.x + yindent * e->cam.up.x + xindent *
		e->cam.right.x;
	ray->dir.y = ZOOM * e->cam.normal.y + yindent * e->cam.up.y + xindent *
		e->cam.right.y;
	ray->dir.z = ZOOM * e->cam.normal.z + yindent * e->cam.up.z + xindent *
		e->cam.right.z;
	normalize(&ray->dir);
}
