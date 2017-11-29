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