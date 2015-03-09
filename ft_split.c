/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/10 17:00:37 by vroche            #+#    #+#             */
/*   Updated: 2015/01/26 15:35:21 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** libft's ft_strsplit adapted for fdf, cut all nbr without precision
*/

#include "fdf.h"

static int		ft_cnt_parts(const char *s)
{
	int		cnt;
	int		in_substring;

	in_substring = 0;
	cnt = 0;
	while (*s != '\0')
	{
		if (in_substring == 1 && !((*s >= '0' && *s <= '9') || \
			(*s >= 'A' && *s <= 'F') || *s == '-' || *s == '+' || \
			*s == ',' || *s == 'x'))
			in_substring = 0;
		if (in_substring == 0 && ((*s >= '0' && *s <= '9') \
			|| *s == '-' || *s == '+' || *s == ',' || *s == 'x'))
		{
			in_substring = 1;
			cnt++;
		}
		s++;
	}
	return (cnt);
}

static int		ft_wlen(const char *s)
{
	int		len;

	len = 0;
	while (((*s >= '0' && *s <= '9') || (*s >= 'A' && *s <= 'F') || *s == '-' \
			|| *s == '+' || *s == ',' || *s == 'x') && *s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

char			**ft_nbrstrsplit(char const *s)
{
	char	**t;
	int		nb_word;
	int		index;

	index = 0;
	nb_word = ft_cnt_parts((const char *)s);
	t = (char **)malloc(sizeof(*t) * (ft_cnt_parts((const char *)s) + 1));
	if (t == NULL)
		return (NULL);
	while (nb_word--)
	{
		while (!((*s >= '0' && *s <= '9') || (*s >= 'A' && *s <= 'F') \
				|| *s == '-' || *s == '+' || *s == ',' || *s == 'x') \
				&& *s != '\0')
			s++;
		t[index] = ft_strsub((const char *)s, 0, ft_wlen((const char *)s));
		if (t[index] == NULL)
			return (NULL);
		s = s + ft_wlen(s);
		index++;
	}
	t[index] = NULL;
	return (t);
}
