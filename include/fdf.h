/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:26:21 by galambey          #+#    #+#             */
/*   Updated: 2023/08/31 17:20:02 by galambey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/ft_printf/include/ft_printf.h"
# include "../libft/get_next_line/includes/get_next_line.h"
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <unistd.h>

# define WIDTH 1920
# define HEIGHT 1015
# define M_PI 3.14159265358979323846

typedef struct s_an
{
	double			d_sin_p;
	double			d_sin_m;
	double			d_cos_p;
	double			d_cos_m;
}					t_an;

typedef struct s_coef
{
	int				pix;
	int				pix_ref;
	int				alt;
	double			z_var;
	double			z_var_ref;
	int				min_z;
	int				max_z;
	int				mid_z;
	double			rot;
	int				mv[7];
	t_an			an;
	int				proj;
}					t_coef;

typedef struct s_img
{
	void			*mlx_img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	t_coef			co;
}					t_img;

typedef struct s_win
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_img			img1;
	t_img			img2;
	t_cont			coord;
}					t_win;

typedef struct s_coord
{
	int				x;
	int				y;
	int				z;
	int				x_p;
	int				y_p;
	double			z_p;
	double			xd_p;
	double			yd_p;
	double			zd_p;
	int				len;
	int				color;
	int				ck_color;
}					t_coord;

typedef struct s_var
{
	int				dx;
	int				dy;
	int				dz;
	int				error;
	int				error_inc;
	int				x_inc;
	int				y_inc;
	int				delta;
	int				color_0;
	int				color_1;
	int				color_inc[4];
	int				c_inc[4];
	float			error_c[4];
	float			error_c_inc[4];
}					t_var;

typedef struct s_color
{
	int				c0[3];
	int				c1[3];
	int				d[4];
	unsigned char	rgb0[4];
	unsigned char	rgb1[4];
}					t_color;

enum				e_statut
{
	V_DFT = -2,
	E_ERR = -1,
	E_OK
};

enum				e_altitude
{
	NR = -2,
	DIFF_Z = -1,
	SAME_Z = 0
};

enum				e_color
{
	n = -2,
	y = -1,
	r = 0,
	g = 1,
	b = 2,
	RGB = 3
};

enum				e_move
{
	RL,
	UD,
	CK,
	U,
	D,
	R,
	L
};

enum				e_projection
{
	isometric,
	parallele
};

/*main.c*/
int					main(int ac, char **av);

/*parsing_utils.c*/
void				ft_atoi_parse_z_and_color(char *str, int *error,
						t_coord *elem);

/*parsing.c*/
t_cont				ft_recup_map(int fd);
int					ft_lstmap_coord(t_cont *coord, char **array, int x,
						int *check);
void				del(void *content);

/*coefficient.c*/
void				ft_get_coef(t_cont *coord, t_coef *co);

/*fdf.c*/
int					ft_fdf(t_cont coord);
void				calcul_iso(void *current, void *prev, t_cont *coord,
						t_coef *co);
void				ft_adapt_z(int *z, double *z_p, t_coef *co);

/*projection*/
void				ft_img_pix_put(t_img *img, t_coord pt);
void				ft_img_iso(t_img *img, t_cont coord);
void				ft_img_para(t_img *img, t_cont coord);

/*projection_utils.c*/
void				ft_first_point(t_coord *pt, t_coord *pt_ref, t_img *img,
						t_cont coord);

/*isometry.c*/
void				ft_calcul_first_pt_iso(t_coord *pt, t_cont coord,
						t_coef *co);
void				ft_calcul_lg_first_pt_iso(t_coord *pt_0, t_coord *pt_1,
						t_coef *co);
void				ft_calcul_pt_iso_else(t_coord *pt_0, t_coord *pt_1,
						t_coef *co);

/*parallele.c*/
void				ft_calcul_first_pt_para(t_coord *pt, t_cont coord,
						t_coef *co);
void				ft_calcul_lg_first_pt_para(t_coord *pt_0, t_coord *pt_1,
						t_coef *co);
void				ft_calcul_pt_para_else(t_coord *pt_0, t_coord *pt_1,
						t_coef *co);

/*color_set.c*/
void				ft_define_color(t_coord pt_0, t_coord pt_1, t_var *var,
						t_coef co);
void				ft_set_rgb(int col, unsigned char *rgb, int *c);

/*color_change*/
void				ft_put_color(t_coord *pt, t_var *var, int ck_color_1);

/*color_map_fade*/
void				ft_color_fade(t_color *color, t_var *var);

/*color_set_error.c*/
void				ft_set_delta(t_color color, t_var *var, int ck_color0,
						int ck_color1);

/*event.c*/
void				ft_reset(t_coef *co);
int					ft_handle_no_event(t_win *win);
int					ft_handle_event(int keysym, t_win *win);

/*event_utils.c*/
void				ft_ev_translate(int keysym, int *mv);
void				ft_ev_zoom(int keysym, t_coef *co);
void				ft_ev_rotate(int keysym, double *rot);
void				ft_ev_elevation(int keysym, t_coef *co);
void				ft_ev_projection(int keysym, t_coef *co);

/*exit.c*/
void				del(void *content);
void				ft_error_list(t_cont coord, char *line, char **array,
						int fd);
int					ft_exit(t_win *win);
void				*ft_free_array(char **array);
int					ft_exit_bis(t_cont *coord, t_win *win);

/*bresenham.c*/
void				ft_draw_line(t_img *img, t_coord pt_0, t_coord pt_1,
						t_coef *co);

/*bresenham_utils.c*/
void				ft_final_coord(t_coord *pt_0, t_coord *pt_1, t_coef *co);

/*translation.c*/
void				ft_translate(double *x, double *y, t_coef *co);
void				ft_ck_translate(t_coord *pt_0, t_coord *pt_1, t_coef *co);
void				ft_reset_ck_translate(t_coef *co);

#endif
