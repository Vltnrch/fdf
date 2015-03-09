/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/26 15:09:15 by vroche            #+#    #+#             */
/*   Updated: 2015/01/26 17:00:00 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** fonction to init conf and manage key touch
** print all key to user on FdF's start
*/

#include "fdf.h"

void	init_conf(t_env *env)
{
	env->bpp = 24;
	env->sizeline = 4 * LENGHT;
	env->endian = 0;
	env->mlx = mlx_init();
	env->img = NULL;
	env->data = NULL;
	env->angle = 0;
	env->zoom = 0;
	env->xm = 0;
	env->ym = 0;
	env->zm = 0;
}

int		key_hook(int keycode, t_env *env)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 2)
		env->angle = (env->angle + M_PI / 4 == 2 * M_PI) \
						? 0 : env->angle + M_PI / 4;
	if (keycode == 0)
		env->angle = (env->angle - M_PI / 4 == -2 * M_PI) \
						? 0 : env->angle - M_PI / 4;
	env->xm = (keycode == 123) ? env->xm - 10 : env->xm;
	env->xm = (keycode == 124) ? env->xm + 10 : env->xm;
	env->zoom = (keycode == 69) ? env->zoom + 2 : env->zoom;
	env->zoom = (keycode == 78) ? env->zoom - 2 : env->zoom;
	env->ym = (keycode == 126) ? env->ym - 10 : env->ym;
	env->ym = (keycode == 125) ? env->ym + 10 : env->ym;
	env->zm = (keycode == 258) ? env->zm - 1 : env->zm;
	env->zm = (keycode == 257) ? env->zm + 1 : env->zm;
	if (keycode == 15)
		init_conf(env);
	ft_fdf(env);
	ft_expose(env);
	return (0);
}

void	ft_printkey(void)
{
	ft_putstr(".:| FdF - Key |:.\n\
.................\n\n\
Up/Down/Left/Right : Move\n\
-/+ : Zoom -/+\n\
a/d : Rotation left/right\n\
Shift/Ctrl : Change z coeff\n\n\
.................\n");
}
