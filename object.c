/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilips <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:10:11 by gphilips          #+#    #+#             */
/*   Updated: 2017/11/29 17:10:12 by gphilips         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	type_object(const char *str)
{
	if (!(ft_strcmp("\tsphere", str)))
		return (SPHERE);
	if (!(ft_strcmp("\tplane", str)))
		return (PLANE);
	if (!(ft_strcmp("\tlight", str)))
		return (LIGHT);
	if (!(ft_strcmp("\tcone", str)))
		return (CONE);
	if (!(ft_strcmp("\tcylinder", str)))
		return (CYLINDER);
	return (0);
}

static int	get_light_info(t_obj *obj, const char **tab, int *i)
{
	int	j;

	if (ft_strncmp("\t\tambient(", tab[*i], 10) ||
			ft_strncmp("\t\tdiffuse(", tab[*i + 1], 10) ||
			ft_strncmp("\t\tspecular(", tab[*i + 2], 11))
		return (0);
	j = 10;
	obj->ambient = ft_atof(tab[*i], &j);
	if (obj->ambient < 0 || obj->ambient >= 1 ||
		tab[*i][j] != ')' || tab[(*i)++][j + 1] != '\0')
		return (0);
	j = 10;
	obj->diffuse = ft_atof(tab[*i], &j);
	if (obj->diffuse < 0 || obj->diffuse >= 1 ||
		tab[*i][j] != ')' || tab[(*i)++][j + 1] != '\0')
		return (0);
	j = 11;
	obj->specular = ft_atof(tab[*i], &j);
	if (obj->specular < 0 || obj->specular >= 1 ||
		tab[*i][j] != ')' || tab[(*i)++][j + 1] != '\0')
		return (0);
	return (1);
}

static int	get_obj(t_list **obj, const char **tab, int *i)
{
	t_obj	*new;
	t_list	*lstnew;

	if (type_object(tab[*i]) == 0)
		return (-1);
	SAFEMALL0((new = (t_obj*)malloc(sizeof(t_obj))));
	new->name = type_object(tab[(*i)++]);
	if (ft_strcmp("\t{", tab[(*i)++]) || !(get_clrpos(new, tab, i)))
		return (0);
	if (new->name != LIGHT)
	{
		if (new->name != PLANE && get_size(new, tab, i) == 0)
			return (0);
		if (new->name != SPHERE && get_normal(new, tab, i) == 0)
			return (0);
		if (get_light_info(new, tab, i) == 0)
			return (0);
	}
	if (ft_strcmp("\t}", tab[*(i++)]))
		return (0);
	new->current = 0;
	SAFEMALL0((lstnew = ft_lstnew(NULL, 0)));
	lstnew->content = new;
	ft_lstadd(obj, lstnew);
	return (1);
}

int			parser_obj(t_list **obj, const char **tab, int i)
{
	while (tab[i] && !(ft_strcmp("", tab[i])))
		++i;
	if (!(tab[i]) || ft_strcmp("content", tab[i++]) || ft_strcmp("{", tab[i++]))
		return (0);
	while (tab[i])
	{
		if (get_obj(obj, tab, &i) == 0)
			return (0);
		else
			++i;
	}
	return (1);
}
