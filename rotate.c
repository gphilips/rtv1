#include "rtv1.h"

static void	rotate_rot(int key, t_vec *nml)
{
	if (key == KEY_1)
		*nml = (t_vec){nml->x * cosf(0.13) + nml->y *
			sinf(-0.13), nml->x * sinf(0.13) + nml->y * cosf(0.13), nml->z};
	if (key == KEY_2)
		*nml = (t_vec){nml->x * cosf(-0.13) + nml->y * sinf(0.13)
			, nml->x * sinf(-0.13) + nml->y * cosf(-0.13), nml->z};
	if (key == KEY_3)
		*nml = (t_vec){nml->x * cosf(0.13) + nml->z * sinf(0.13)
			, nml->y, nml->x * sinf(-0.13) + nml->z * cosf(0.13)};
	if (key == KEY_4)
		*nml = (t_vec){nml->x * cosf(-0.13) + nml->z *
			sinf(-0.13), nml->y, nml->x * sinf(0.13) + nml->z * cosf(-0.13)};
	if (key == KEY_5)
		*nml = (t_vec){nml->x, nml->y * cosf(0.13) + nml->z *
			sinf(-0.13), nml->y * sinf(0.13) + nml->z * cosf(0.13)};
	if (key == KEY_6)
		*nml = (t_vec){nml->x, nml->y * cosf(-0.13) + nml->z *
			sinf(0.13), nml->y * sinf(-0.13) + nml->z * cosf(-0.13)};
}

void		rotate(int key, t_env *e)
{
	if (e->is_obj_selected != 1)
	{
		rotate_rot(key, &e->cam.pos);
		rotate_rot(key, &e->cam.dir);
	}
	else
		rotate_rot(key, &e->hit_obj->normal);
}