/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/10 14:57:32 by vroche            #+#    #+#             */
/*   Updated: 2015/03/09 11:57:52 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_put_pixel_to_image (all is said)
** get_listsize : get max size of all list
** ft_expose : put image to window
** ft_error to manage error message and exit program
*/

#include "fdf.h"

void		ft_put_pixel_to_image(unsigned long img_color, \
									t_env *env, int x, int y)
{
	unsigned char color1;
	unsigned char color2;
	unsigned char color3;
	unsigned char color4;

	if (x > 0 && x < LENGHT && y > 0 && y < HEIGHT)
	{
		color1 = (img_color & 0xFF000000) >> 24;
		color2 = (img_color & 0xFF0000) >> 16;
		color3 = (img_color & 0xFF00) >> 8;
		color4 = (img_color & 0xFF);
		env->data[y * env->sizeline + x * env->bpp / 8] = color4;
		env->data[y * env->sizeline + x * env->bpp / 8 + 1] = color3;
		env->data[y * env->sizeline + x * env->bpp / 8 + 2] = color2;
		env->data[y * env->sizeline + x * env->bpp / 8 + 3] = color1;
	}
}

static void	get_listsize(t_env *env, t_fdf *list)
{
	env->lmax = 0;
	while (list != NULL)
	{
		env->lmax = (list->content_size - 1 > env->lmax) \
					? list->content_size - 1 : env->lmax;
		list = list->next;
	}
}

t_fdf		*get_file(char *file, t_env *env)
{
	int		fd;
	char	*line;
	t_fdf	*list;
	t_fdf	*first;

	fd = open(file, O_RDONLY);
	first = NULL;
	while (get_next_line(fd, &line) > 0 && errno == 0)
	{
		list = ft_lstnew_fdf(ft_nbrstrsplit(line));
		if (first == NULL)
			first = list;
		else
			ft_lstadd_back_fdf(first, list);
		ft_memdel((void **)&line);
	}
	if (errno != 0)
		ft_error(errno, file);
	ft_memdel((void **)&line);
	close(fd);
	env->hmax = ft_list_size_fdf(first);
	get_listsize(env, first);
	env->fdf = first;
	return (first);
}

int			ft_expose(t_env *env)
{
	if (!mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0))
	{
		ft_putstr_fd("mlx_new_window() fails to create a new window\n", 2);
		exit(0);
	}
	return (0);
}

void		ft_error(int errnum, char *s)
{
	perror(s);
	strerror(errnum);
	exit(0);
}
