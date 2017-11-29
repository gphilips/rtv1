#include "rtv1.h"

int		get_clrpos(t_obj *obj, const char **tab, int *i)
{
	int		j;
	double	check;

	if (ft_strncmp("\t\tclr(", tab[*i], 6))
		return (0);
	j = 6;
	if (((check = ft_atof(tab[*i], &j)) < 0) || check > 255)
		return (0);
	obj->color.r = (int)check;
	if (((check = ft_atof(tab[*i], &j)) < 0) || check > 255)
		return (0);
	obj->color.g = (int)check;
	if (((check = ft_atof(tab[*i], &j)) < 0) || check > 255)
		return (0);
	obj->color.b = (int)check;
	if (tab[*i][j] != ')' || tab[*i][j + 1]
		|| ft_strncmp("\t\tpos(", tab[++(*i)], 6))
		return (0);
	j = 6;
	SAFEMALL0((input_vector(tab[*i], &j, &obj->pos)));
	++(*i);
	return (1);
}

int		get_size(t_obj *obj, const char **tab, int *i)
{
	int	j;

	if (ft_strncmp("\t\tsize(", tab[*i], 7))
		return (0);
	j = 7;
	obj->size = ft_atof(tab[*i], &j);
	while (ft_isdigit(tab[*i][j]))
		++j;
	if (tab[*i][j] != ')' || tab[*i][j + 1])
		return (0);
	++(*i);
	return (1);
}

int		get_normal(t_obj *obj, const char **tab, int *i)
{
	int	j;

	if (ft_strncmp("\t\tnml(", tab[*i], 6))
		return (0);
	j = 6;
	SAFEMALL0((input_vector(tab[*i], &j, &obj->normal)));
	++(*i);
	return (1);
}