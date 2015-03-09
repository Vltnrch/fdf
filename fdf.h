/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/08 18:32:24 by vroche            #+#    #+#             */
/*   Updated: 2015/03/09 11:46:36 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <unistd.h>
# include <mlx.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include "mlx.h"
# include "libft.h"

# define ANGLE (M_PI / 6)
# define LARGEUR 10
# define HAUTEUR 10
# define LENGHT 1300
# define HEIGHT 800
# define COEF 2

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	void			*img;
	double			x;
	double			y;
	int				hmax;
	int				lmax;
	int				bpp;
	int				sizeline;
	int				endian;
	double			angle;
	int				zoom;
	int				xm;
	int				ym;
	int				zm;
	char			*data;
	struct s_fdf	*fdf;
}					t_env;

typedef struct		s_fdf
{
	char			**content;
	int				content_size;
	struct s_fdf	*next;
}					t_fdf;

typedef struct		s_draw
{
	int				dx;
	int				dy;
	int				i;
	int				xinc;
	int				yinc;
	int				cumul;
	int				x;
	int				y;
}					t_draw;

typedef struct		s_posxy
{
	double			xi;
	double			yi;
	double			xf;
	double			yf;
	int				ih;
	int				il;
	int				i;
	double			ix;
	double			iy;
	double			hcos;
	double			hsin;
	double			lcos;
	double			lsin;
}					t_posxy;

t_fdf				*ft_lstnew_fdf(char **content);
void				ft_lstadd_back_fdf(t_fdf *alst, t_fdf *new);
int					ft_list_size_fdf(t_fdf *begin_list);

void				ft_draw_line(t_posxy *pos, t_env *env, int color);

char				**ft_nbrstrsplit(char const *s);

void				ft_put_pixel_to_image(unsigned long img_color, \
											t_env *env, int x, int y);
t_fdf				*get_file(char *file, t_env *env);
void				init_conf(t_env *env, int r);
int					key_hook(int keycode, t_env *env);
void				ft_error(int errnum, char *s);

int					ft_fdf(t_env *env);
int					ft_expose(t_env *env);
void				ft_printkey(void);

#endif
