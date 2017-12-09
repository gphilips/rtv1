/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilips <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:10:40 by gphilips          #+#    #+#             */
/*   Updated: 2017/12/09 15:52:53 by gphilips         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>

# include <stdio.h>

# define WIDTH			1000
# define HEIGHT			700

# define ESC 			53
# define KEY_P 			35
# define KEY_L 			37
# define KEY_PLUS 		69
# define KEY_MOINS 		78
# define KEY_LEFT		123
# define KEY_RIGHT		124
# define KEY_UP			125
# define KEY_DOWN 		126
# define KEY_R 			15
# define KEY_1 			18
# define KEY_2 			19
# define KEY_3 			20
# define KEY_PAD_1 		83
# define KEY_PAD_2 		84
# define KEY_PAD_4 		86
# define KEY_PAD_5		87
# define KEY_PAD_7		89
# define KEY_PAD_8		91
# define KEY_TAB		48
# define KEYPRESS 		2
# define KEYPRESSMASK 	(1L<<0)
# define CLOSE 			17
# define CLOSEMASK 		(1L<<17)

# define SPHERE			1
# define PLANE			2
# define LIGHT			3
# define CONE			4
# define CYLINDER		5

# define INIT 			0
# define ADD 			1
# define SUM 			2

# define ZOOM			2
# define MIN			0.0001
# define MAX			1000.0
# define MAX_LIGHT		10

# define SAFEMALL(x) if (!x) return (NULL);
# define SAFEMALL0(x) if (!x) return (0);
# define SAFEMALL1(x) if (!x) return (-1);

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct		s_vec
{
	double			x;
	double			y;
	double			z;
}					t_vec;

typedef struct		s_ray
{
	t_vec			origin;
	t_vec			dir;
}					t_ray;

typedef struct		s_cam
{
	t_vec			pos;
	t_vec			dir;
	t_vec			lookat;
	t_vec			normal;
	t_vec			right;
	t_vec			up;
}					t_cam;

typedef struct		s_solver
{
	t_vec			dist;
	double			a;
	double			b;
	double			c;
	double			deter;
	double			t1;
	double			t2;
}					t_solver;

typedef struct		s_hit
{
	t_ray			*ray_origin;
	t_vec			point;
	t_vec			normal;
	t_color			color;
	double			t;
}					t_hit;

typedef struct		s_obj
{
	int				name;
	t_vec			pos;
	t_color			color;
	double			size;
	t_vec			normal;
	double			ambient;
	double			diffuse;
	double			specular;
	int				current;
}					t_obj;


typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	void			*img_tex;
	char			*data;
	int				sl;
	int				endian;
	int				bpp;
}					t_mlx;

typedef struct		s_env
{
	t_mlx			mlx;
	t_cam			cam;
	char			**tab;
	t_list			*obj;
	t_vec			n;
	t_vec			right;
	t_vec			up;
	double			aa;
	double			t;
	double			p;
	t_obj			*hit_obj;
	int				is_obj_selected;
	int 			zoom;
	t_obj			*light[MAX_LIGHT];
	int				l;
	int				total_light;
	//int				help;
}					t_env;

/*
**	main.c
*/
int					error(char *str);
void				display_instruction(void);
void				put_image(t_env *e);

/*
**	scene.c
*/
int					get_scene(t_env *e, char *file);
int					input_vector(const char *str, int *i, t_vec *vec);

/*
**	object.c
*/
int					parser_obj(t_list **obj, const char **tab, int i);

/*
**	get.c
*/
int					get_clrpos(t_obj *obj, const char **tab, int *i);
int					get_size(t_obj *obj, const char **tab, int *i);
int					get_normal(t_obj *obj, const char **tab, int *i);
void				get_light(t_env *e);

/*
**	ft_atof.c
*/
double				ft_atof(const char *nb, int *i);

/*
**	draw.c
*/
void				draw_screen(t_env *e);

/*
**	ray.c
*/
void				current_ray(double x, double y, t_env *e, t_ray *ray);

/*
**	closest_t.c
*/
double				find_closest_t(t_list *list, t_ray *ray, t_obj **hit_obj);

/*
**	inter.c
*/
double				sphere_inter(t_obj *obj, t_ray *ray);
double				cylinder_inter(t_obj *obj, t_ray *ray);
double				cone_inter(t_obj *obj, t_ray *ray);
double				plane_inter(t_obj *obj, t_ray *ray);

/*
**	inter_utils.c
*/
double				solver(t_solver *s);
void				get_hit_point_info(t_hit *hit_point, t_obj *obj, t_ray *ray);

/*
**	color.c
*/
t_color				lighting(t_list *list, t_obj **obj, t_ray ray, double t);

/*
**	vector_op.c
*/
t_vec				vec_add(t_vec *v1, t_vec *v2);
t_vec				vec_sub(t_vec *v1, t_vec *v2);
t_vec				vec_scale(double scale, t_vec *v1);
t_vec				vec_negative(t_vec *v);
t_vec				vec_cross(t_vec *v1, t_vec *v2);

/*
**	vector_op2.c
*/
double				dot(t_vec *v1, t_vec *v2);
void				normalize(t_vec *v1);

/*
**	hook.c
*/
int					key_hook(int key, t_env *e);
int 				mouse_hook(int button, int x, int y, t_env *e);
int					quit(t_env *e);

/*
**	display.c
*/
void				display_info(t_env *e);

/*
**	translate.c
*/
void				translate(int key, t_env *e);

/*
**	rotate.c
*/
void				rotate(int key, t_env *e);
#endif
