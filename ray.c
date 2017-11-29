#include "rtv1.h"

void	current_ray(double x, double y, t_env *e, t_ray *ray)
{
	double	xindent;
	double	yindent;

	e->cam.normal = vec_sub(&e->cam.dir, &e->cam.pos);
	normalize(&e->cam.normal);
	e->cam.right = vec_cross(&e->cam.normal, &e->up);
	normalize(&e->cam.right);
	e->cam.up = vec_cross(&e->cam.right, &e->cam.normal);
	xindent = (WIDTH - x * 2.0) / HEIGHT;
	yindent = (HEIGHT - y * 2.0) / WIDTH;
	ray->origin.x = e->cam.pos.x;
	ray->origin.y = e->cam.pos.y;
	ray->origin.z = e->cam.pos.z;
	ray->dir.x = e->zoom * e->cam.normal.x + yindent * e->cam.up.x + xindent *
		e->cam.right.x;
	ray->dir.y = e->zoom * e->cam.normal.y + yindent * e->cam.up.y + xindent *
		e->cam.right.y;
	ray->dir.z = e->zoom * e->cam.normal.z + yindent * e->cam.up.z + xindent *
		e->cam.right.z;
	normalize(&ray->dir);
}