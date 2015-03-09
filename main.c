/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/02 15:57:14 by vroche            #+#    #+#             */
/*   Updated: 2015/03/09 11:46:20 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** FdF main
** manage color, draw with pecpective and init
*/

#include "fdf.h"
#include <stdio.h>

static void ft_fdf_draw(t_posxy *pos, t_env *env, int z)
{
	int color;

	if (z <= -40)
		color = 0x0000FF;
	else if (z < -10)
		color = 0xF0F000;
	else if (z >= -10 && z <= 10)
		color = 0x00A000;
	else if (z >= 30)
		color = 0xFFFFFF;
	else
		color = 0x702E00;
	ft_draw_line(pos, env, color);
}

static void	ft_fdf_part(t_posxy *pos, t_env *env, t_fdf *fdf)
{
	int	z;

	pos->xi = env->x;
	pos->yi = env->y - ((pos->i < fdf->content_size - 1) \
				? ft_atoi(fdf->content[pos->i]) * (COEF + env->zm) : 0);
	if (fdf->next != NULL && pos->ih < env->hmax - 1)
	{
		z = (pos->i < fdf->next->content_size - 1) \
			? ft_atoi(fdf->next->content[pos->i]) * (COEF + env->zm) : 0;
		pos->xf = env->x + ((HAUTEUR + env->zoom) * pos->hcos);
		pos->yf = env->y + ((HAUTEUR + env->zoom) * pos->hsin) - z;
		ft_fdf_draw(pos, env, z);
	}
	if (pos->il < env->lmax - 1)
	{
		z = (pos->i + 1 < fdf->content_size - 1) \
			? ft_atoi(fdf->content[pos->i + 1]) * (COEF + env->zm) : 0;
		pos->xf = env->x + ((LARGEUR + env->zoom) * pos->lcos);
		pos->yf = env->y + ((LARGEUR + env->zoom) * pos->lsin) - z;
		ft_fdf_draw(pos, env, z);
	}
	env->x = env->x + ((LARGEUR + env->zoom) * pos->lcos);
	env->y = env->y + ((LARGEUR + env->zoom) * pos->lsin);
	pos->il++;
	pos->i++;
}

static void	ft_fdf_init(t_posxy *pos, t_env *env)
{
	pos->hcos = cos(ANGLE + env->angle + (2 * M_PI / 3));
	pos->hsin = sin(ANGLE + env->angle + (2 * M_PI / 3));
	pos->lcos = cos(ANGLE + env->angle);
	pos->lsin = sin(ANGLE + env->angle);
	pos->ix = LENGHT / 2 - ((LARGEUR + env->zoom) * env->lmax) / 2 + env->xm;
	pos->iy = HEIGHT / 2 - ((HAUTEUR + env->zoom) * env->hmax) / 2 + env->ym;
}

int			ft_fdf(t_env *env)
{
	t_posxy	pos;
	t_fdf	*fdf;

	pos.ih = 0;
	fdf = env->fdf;
	if (env->data != NULL)
		mlx_destroy_image(env->mlx, env->img);
	env->img = mlx_new_image(env->mlx, LENGHT, HEIGHT);
	env->data = mlx_get_data_addr(env->img, &(env->bpp), \
				&(env->sizeline), &(env->endian));
	ft_fdf_init(&pos, env);
	while (pos.ih < env->hmax)
	{
		pos.il = 0;
		pos.i = 0;
		env->x = pos.ix + pos.ih * ((HAUTEUR + env->zoom) * pos.hcos);
		env->y = pos.iy + pos.ih * ((HAUTEUR + env->zoom) * pos.hsin);
		while (pos.il < env->lmax)
			ft_fdf_part(&pos, env, fdf);
		fdf = fdf->next;
		pos.ih++;
	}
	return (0);
}

int			main(int ac, char **av)
{
	t_env	env;

	if (ac >= 2)
		get_file(av[1], &env);
	else
	{
		ft_putstr("usage : ");
		ft_putstr(av[0]);
		ft_putendl(" file1");
		return (0);
	}
	ft_printkey();
	init_conf(&env, 0);
	env.win = mlx_new_window(env.mlx, LENGHT, HEIGHT, "FdF");
	ft_fdf(&env);
	mlx_expose_hook(env.win, ft_expose, &env);
	mlx_key_hook(env.win, key_hook, &env);
	mlx_loop(env.mlx);
	return (0);
}
