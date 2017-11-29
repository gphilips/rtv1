#include "rtv1.h"

t_vec	vec_add(t_vec *v1, t_vec *v2)
{
	t_vec	v;

	v.x = v1->x + v2->x;
	v.y = v1->y + v2->y;
	v.z = v1->z + v2->z;
	return (v);
}

t_vec	vec_sub(t_vec *v1, t_vec *v2)
{
	t_vec	v;

	v.x = v1->x - v2->x;
	v.y = v1->y - v2->y;
	v.z = v1->z - v2->z;
	return (v);
}

t_vec	vec_scale(double scale, t_vec *v1)
{
	t_vec	v;

	v.x = scale * v1->x;
	v.y = scale * v1->y;
	v.z = scale * v1->z;
	return (v);
}

t_vec	vec_negative(t_vec *v)
{
	t_vec	n;

	n.x = -v->x;
	n.y = -v->y;
	n.z = -v->z;
	return (n);
}


t_vec 	vec_cross(t_vec *v1, t_vec *v2)
{
	t_vec	v;

	v.x = v1->y * v2->z - v1->z * v2->y;
	v.y = v2->x * v1->z - v2->z * v1->x;
	v.z = v1->x * v2->y - v1->y * v2->x;
	return (v);
}