/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/08 19:17:26 by vroche            #+#    #+#             */
/*   Updated: 2015/01/26 15:36:21 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** chained list fonction for fdf
*/

#include "fdf.h"

t_fdf	*ft_lstnew_fdf(char **content)
{
	t_fdf	*list;
	int		content_size;

	if (!(list = (t_fdf *)ft_memalloc(sizeof(t_fdf))))
		return (NULL);
	list->content = content;
	if (*content == 0)
		content_size = 0;
	else
	{
		content_size = 1;
		while (*content++ != 0)
			content_size++;
	}
	list->content_size = content_size;
	list->next = NULL;
	return (list);
}

void	ft_lstadd_back_fdf(t_fdf *alst, t_fdf *new)
{
	if (new && alst)
	{
		while (alst->next != NULL)
			alst = alst->next;
		alst->next = new;
	}
}

int		ft_list_size_fdf(t_fdf *begin_list)
{
	t_fdf	*tmp;
	int		i;

	i = 1;
	tmp = begin_list;
	if (tmp == NULL)
		return (0);
	while (tmp->next != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
