/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min_max.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilips <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 21:05:52 by gphilips          #+#    #+#             */
/*   Updated: 2016/11/19 15:32:56 by gphilips         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_min_max(double x, double min, double max)
{
	if (x < min)
		x = min;
	else if (x > max)
		x = max;
	return (x);
}
