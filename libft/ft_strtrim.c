/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 15:48:47 by vroche            #+#    #+#             */
/*   Updated: 2014/11/13 17:53:57 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\n' || c == '\t' \
		|| c == '\r' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

char		*ft_strtrim(char const *s)
{
	size_t	len;
	char	*dest;

	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) == 0)
		return ((char *)s);
	while (*s && ft_isspace(*s))
		s++;
	len = ft_strlen(s);
	while (*s && ft_isspace(s[--len]))
		;
	if (!(dest = ft_strnew(len)))
		return (NULL);
	dest = ft_strncpy(dest, s, len + 1);
	dest[len + 1] = '\0';
	return (dest);
}
