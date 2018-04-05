/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilips <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 16:13:36 by gphilips          #+#    #+#             */
/*   Updated: 2017/12/22 16:14:25 by gphilips         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double			solver(t_solver *s)
{
	s->deter = s->b * s->b - 4.0 * s->a * s->c;
	if (s->deter < MIN)
		return (-1.0);
	s->t1 = (-s->b + sqrtf(s->deter)) / ((double)s->a * 2);
	s->t2 = (-s->b - sqrtf(s->deter)) / ((double)s->a * 2);
	if (s->t1 >= MIN && s->t2 >= MIN)
		return ((s->t1 < s->t2) ? s->t1 : s->t2);
	else if (s->t1 * s->t2 <= MIN)
		return ((s->t1 >= MIN) ? s->t1 : s->t2);
	else
		return (-1.0);
}

static void		get_hit_point_normal(t_hit *hit_point, t_obj *obj, t_ray *ray)
{
	double		m;
	t_vec		dist;
	t_vec		left;
	t_vec		right;

	if (obj->name == SPHERE)
		hit_point->normal = vec_sub(&hit_point->point, &obj->pos);
	if (obj->name == PLANE)
	{
		hit_point->normal = (dot(&ray->dir, &obj->normal) > 0.0) ?
			vec_scale(-1.0, &obj->normal) : obj->normal;
	}
	if (obj->name == CONE || obj->name == CYLINDER)
	{
		dist = vec_sub(&ray->origin, &obj->pos);
		m = hit_point->t * dot(&ray->dir, &obj->normal) +
			dot(&dist, &obj->normal);
		left = vec_sub(&hit_point->point, &obj->pos);
		if (obj->name == CONE)
			right = vec_scale((1 + pow(tan(obj->size), 2)) * m, &obj->normal);
		else
			right = vec_scale(m, &obj->normal);
		hit_point->normal = vec_sub(&left, &right);
	}
}

void			get_hit_point_info(t_hit *hit_point, t_obj *obj, t_ray *ray)
{
	hit_point->ray_origin = ray;
	hit_point->point.x = ray->origin.x + hit_point->t * ray->dir.x;
	hit_point->point.y = ray->origin.y + hit_point->t * ray->dir.y;
	hit_point->point.z = ray->origin.z + hit_point->t * ray->dir.z;
	get_hit_point_normal(hit_point, obj, ray);
	normalize(&hit_point->normal);
}
