#include "rtv1.h"

static void	repere(t_env *e)
{
	e->n = vec_sub(&e->cam.dir, &e->cam.pos);
	normalize(&e->n);
	e->right = vec_cross(&e->n, &(t_vec){0.0, 1.0, 0.0});
	normalize(&e->right);
	e->up = vec_cross(&e->right, &e->n);
	normalize(&e->up);
}

static void	translate_pos(int key, t_vec *pos, t_env *e)
{
	t_vec	tmp;

	tmp = *pos;
	if (key == KEY_LEFT)
		*pos = (t_vec){tmp.x + e->right.x * 10.0,
			tmp.y + e->right.y * 10.0, tmp.z + e->right.z * 10.0};
	else if (key == KEY_RIGHT)
		*pos = (t_vec){tmp.x - e->right.x * 10.0, tmp.y
			- e->right.y * 10.0, tmp.z - e->right.z * 10.0};
	else if (key == KEY_DOWN)
		*pos = (t_vec){tmp.x + e->up.x * 10.0,
			tmp.y + e->up.y * 10.0, tmp.z + e->up.z * 10.0};
	else if (key == KEY_UP)
		*pos = (t_vec){tmp.x - e->up.x * 10.0,
			tmp.y - e->up.y * 10.0, tmp.z - e->up.z * 10.0};
	else if (key == KEY_P)
		*pos = (t_vec){tmp.x + e->n.x * 10.0,
			tmp.y + e->n.y * 10.0, tmp.z + e->n.z * 10.0};
	else if (key == KEY_L)
		*pos = (t_vec){tmp.x - e->n.x * 10.0, tmp.y -
			e->n.y * 10.0, tmp.z - e->n.z * 10.0};
}

void		translate(int key, t_env *e)
{
	repere(e);
	if (e->is_obj_selected == 1)
		translate_pos(key, &e->hit_obj->pos, e);
	else
	{
		translate_pos(key, &e->cam.pos, e);
		translate_pos(key, &e->cam.dir, e);
	}
	if (key == KEY_R)
	{
		e->is_obj_selected = 0;
		e->hit_obj = NULL;
	}
}