/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilips <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:09:31 by gphilips          #+#    #+#             */
/*   Updated: 2017/12/22 16:08:39 by gphilips         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				error(char *str)
{
	ft_putendl(str);
	exit(1);
}

static void		*init_env(t_env *e)
{
	SAFEMALL((e->mlx.mlx = mlx_init()));
	SAFEMALL((e->mlx.win = mlx_new_window(e->mlx.mlx, WIDTH, HEIGHT, "Rtv1")));
	SAFEMALL((e->mlx.img = mlx_new_image(e->mlx.mlx, WIDTH, HEIGHT)));
	e->mlx.data = mlx_get_data_addr(e->mlx.img, &(e->mlx.bpp),
						&(e->mlx.sl), &(e->mlx.endian));
	e->hit_obj = NULL;
	e->aa = 1.0;
	e->up = (t_vec){0.0, 1.0, 0.0};
	e->obj = NULL;
	e->is_obj_selected = 0;
	e->l = -1;
	return (0);
}

void			put_image(t_env *e)
{
	int		w;
	int		h;

	mlx_clear_window(e->mlx.mlx, e->mlx.win);
	if (e->is_obj_selected != 1)
	{
		e->mlx.img_tex = mlx_xpm_file_to_image(e->mlx.mlx,
			"./scenes/rt.xpm", &w, &h);
	}
	else
	{
		e->mlx.img_tex = mlx_xpm_file_to_image(e->mlx.mlx,
						"./scenes/rt_obj.xpm", &w, &h);
	}
	mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, e->mlx.img, 0, 0);
	mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, e->mlx.img_tex, 0, 0);
	display_info(e);
}

int				main(int argc, char **argv)
{
	t_env	e;

	if (argc != 2)
		error("Usage : ./rtv1 <scene>");
	init_env(&e);
	if (get_scene(&e, argv[1]) == 0)
		error("Error: something is wrong with the parsing of the scene");
	display_instruction();
	draw_screen(&e);
	put_image(&e);
	get_light(&e);
	mlx_hook(e.mlx.win, CLOSE, CLOSEMASK, quit, &(e.mlx));
	mlx_mouse_hook(e.mlx.win, mouse_hook, &(e.mlx));
	mlx_hook(e.mlx.win, KEYPRESS, KEYPRESSMASK, key_hook, &(e.mlx));
	mlx_loop(e.mlx.mlx);
	return (0);
}
