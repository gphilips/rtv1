/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilips <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 20:19:31 by gphilips          #+#    #+#             */
/*   Updated: 2017/12/22 17:37:01 by gphilips         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		nb_len(const char *nb)
{
	int				i;

	i = 0;
	while (nb[i] && ft_isdigit(nb[i]))
		i++;
	return (i);
}

static double	get_integer_part(const char *nb, int *i)
{
	int				exp;
	int				len;
	double			result;

	result = 0;
	exp = 1;
	len = nb_len(&nb[*i]);
	while (1 < len)
	{
		exp *= 10;
		len--;
	}
	while (nb[*i] && ft_isdigit(nb[*i]))
	{
		result += (nb[*i] - '0') * exp;
		exp /= 10;
		(*i)++;
	}
	if (nb[*i] == '.')
		(*i)++;
	return (result);
}

static double	get_float_part(int neg, double result, const char *nb, int *i)
{
	int				exp;

	exp = 10;
	while (nb[*i] && ft_isdigit(nb[*i]))
	{
		result += (double)(nb[*i] - '0') / exp;
		exp *= 10;
		(*i)++;
	}
	if (neg == 1)
		result = -result;
	return (result);
}

double			ft_atof(const char *nb, int *i)
{
	int				neg;
	double			result;

	while (ft_iswhitespace(nb[*i]))
		(*i)++;
	if (nb[*i] == '-')
	{
		(*i)++;
		neg = 1;
	}
	else
		neg = 0;
	result = get_integer_part(nb, i);
	result = get_float_part(neg, result, nb, i);
	return (result);
}
