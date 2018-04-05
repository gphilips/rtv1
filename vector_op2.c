/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilips <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:09:43 by gphilips          #+#    #+#             */
/*   Updated: 2017/12/22 16:13:13 by gphilips         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	dot(t_vec *v1, t_vec *v2)
{
	double	ret;

	ret = (v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z);
	return (ret);
}

void	normalize(t_vec *v1)
{
	double	norm;

	norm = 1.0 / sqrtf(v1->x * v1->x + v1->y * v1->y + v1->z * v1->z);
	v1->x = v1->x * norm;
	v1->y = v1->y * norm;
	v1->z = v1->z * norm;
}
