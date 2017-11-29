#include "rtv1.h"

int				error(char *str)
{
	ft_putendl(str);
	exit(1);
}

static char		**init_tab(void)
{
	char	**tab;

	SAFEMALL((tab = (char**)malloc(sizeof(char*) * 6)));
	tab[0] = ft_strdup("light");
	tab[1] = ft_strdup("plane");
	tab[2] = ft_strdup("cylinder");
	tab[3] = ft_strdup("cone");
	tab[4] = ft_strdup("sphere");
	tab[5] = NULL;
	return (tab);
}

static void		*init_env(t_env *e)
{
	SAFEMALL((e->mlx.mlx = mlx_init()));
	SAFEMALL((e->mlx.win = mlx_new_window(e->mlx.mlx, WIDTH, HEIGHT, "Rtv1")));
	SAFEMALL((e->mlx.img = mlx_new_image(e->mlx.mlx, WIDTH, HEIGHT)));
	e->mlx.data = mlx_get_data_addr(e->mlx.img, &(e->mlx.bpp),
						&(e->mlx.sl), &(e->mlx.endian));
	SAFEMALL((e->tab = init_tab()));
	e->hit_obj = NULL;
	e->aa = 1.0;
	e->up = (t_vec){0.0, 1.0, 0.0};
	e->obj = NULL;
	e->is_obj_selected = 0;
	e->help = -1;
	e->l = -1;
	e->zoom = 2;
	return (0);
}

void		put_image(t_env *e)
{
	mlx_clear_window(e->mlx.mlx, e->mlx.win);
	mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, e->mlx.img, 0, 0);
}

int				main(int argc, char **argv)
{
	t_env	e;

	if (argc != 2)
		error("Usage : ./rtv1 <scene>");
	init_env(&e);
	if (get_scene(&e, argv[1]) == 0)
		error("Error: something is wrong with the parsing of the scene");
	draw_screen(&e);
	put_image(&e);
	// light_position(&e);
	//mlx_mouse_hook(e.mlx.win, mouse_hook_func, &(e.mlx));
	mlx_hook(e.mlx.win, KEYPRESS, KEYPRESSMASK, key_hook, &(e.mlx));
	mlx_loop(e.mlx.mlx);
	return (0);
}