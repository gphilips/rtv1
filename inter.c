/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilips <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:11:29 by gphilips          #+#    #+#             */
/*   Updated: 2017/11/29 17:11:31 by gphilips         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	sphere_inter(t_obj *obj, t_ray *ray)
{
	double		t;
	t_solver	s;

	s.dist = vec_sub(&ray->origin, &obj->pos);
	s.a = dot(&ray->dir, &ray->dir);
	s.b = 2.0 * dot(&ray->dir, &s.dist);
	s.c = dot(&s.dist, &s.dist) - (obj->size * obj->size);
	t = solver(&s);
	return (t);
}

double	plane_inter(t_obj *obj, t_ray *ray)
{
	double		t;
	t_solver	s;

	s.dist = vec_sub(&ray->origin, &obj->pos);
	t = -1.0 * dot(&obj->normal, &s.dist) / dot(&obj->normal, &ray->dir);
	return ((t < MIN) ? -1 : t);
}

double	cylinder_inter(t_obj *obj, t_ray *ray)
{
	double		t;
	t_solver	s;

	s.dist = vec_sub(&ray->origin, &obj->pos);
	normalize(&obj->normal);
	s.a = dot(&ray->dir, &ray->dir) -
		pow(dot(&obj->normal, &ray->dir), 2);
	s.b = 2.0 * (dot(&s.dist, &ray->dir) -
			(dot(&obj->normal, &s.dist) * dot(&obj->normal, &ray->dir)));
	s.c = dot(&s.dist, &s.dist) -
		pow(dot(&obj->normal, &s.dist), 2) - obj->size * obj->size;
	t = solver(&s);
	return (t);
}

double	cone_inter(t_obj *obj, t_ray *ray)
{
	double		t;
	t_solver	s;

	s.dist = vec_sub(&ray->origin, &obj->pos);
	normalize(&obj->normal);
	s.a = dot(&ray->dir, &ray->dir) - (1 + pow(tan(obj->size), 2)) *
		pow(dot(&ray->dir, &obj->normal), 2);
	s.b = 2 * (dot(&ray->dir, &s.dist) - (1 + pow(tan(obj->size), 2))
			* dot(&ray->dir, &obj->normal) * dot(&s.dist, &obj->normal));
	s.c = dot(&s.dist, &s.dist) -
		(1 + pow(tan(obj->size), 2)) * pow(dot(&s.dist, &obj->normal), 2);
	t = solver(&s);
	return (t);
}
