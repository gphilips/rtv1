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
# define KEY_1			18
# define KEY_2 			19
# define KEY_3 			20
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

# define MIN			0.0001
# define MAX			8000.0

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
	t_vec			r;
	t_vec			up;
	double			aa;
	double			t;
	double			p;
	t_obj			*hit_obj;
	int				is_obj_selected;
	int 			zoom;
	// t_obj		*light[MAX_LIGHT];
	int				l;
	// int			total_light;
	int				help;
	// char			*itoapos;
	// char			*itoasize;
	// char			*itoarot;
	// char			*itoacampos;
	// char			*itoacamdir;
}					t_env;

/*
**	main.c
*/
int					error(char *str);
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

#endif