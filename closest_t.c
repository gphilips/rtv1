/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_t.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilips <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:11:54 by gphilips          #+#    #+#             */
/*   Updated: 2017/11/29 17:11:55 by gphilips         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	get_tmp(double *tmp, t_obj *obj, t_ray *ray)
{
	if (obj->name == SPHERE)
		*tmp = sphere_inter(obj, ray);
	else if (obj->name == PLANE)
		*tmp = plane_inter(obj, ray);
	else if (obj->name == CYLINDER)
		*tmp = cylinder_inter(obj, ray);
	else if (obj->name == CONE)
		*tmp = cone_inter(obj, ray);
}

double		find_closest_t(t_list *list, t_ray *ray, t_obj **hit_obj)
{
	t_list		*node;
	t_obj		*obj;
	double		t;
	double		tmp;

	t = MAX;
	tmp = MAX;
	node = list;
	while (node)
	{
		obj = (t_obj*)node->content;
		if (obj->name != LIGHT && obj->current == 0)
			get_tmp(&tmp, obj, ray);
		if (tmp >= MIN && tmp < t)
		{
			t = tmp;
			*hit_obj = obj;
		}
		node = node->next;
	}
	if (t >= MIN && t < MAX && (*hit_obj))
		(*hit_obj)->current = 1;
	return (t);
}
