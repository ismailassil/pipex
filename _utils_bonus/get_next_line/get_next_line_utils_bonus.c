/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:30:29 by iassil            #+#    #+#             */
/*   Updated: 2024/01/12 23:01:42 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_str_len(char *str)
{
	size_t	len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

char	*ft_c_alloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = malloc(count * size);
	if (ptr != NULL)
	{
		while (i < count)
			ptr[i++] = '\0';
		return (ptr);
	}
	return (NULL);
}

size_t	ft_str_chr(const char *str)
{
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	if (*str == '\n')
		return (1);
	return (0);
}

char	*ft_str_join(char **s1, char *s2)
{
	char	*ptr;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_str_len((*s1)) + ft_str_len(s2);
	ptr = ft_c_alloc((len + 1), sizeof(char));
	if (!ptr)
		return (free((*s1)), (*s1) = NULL, NULL);
	while ((*s1) && (*s1)[i])
	{
		ptr[i] = (*s1)[i];
		i++;
	}
	len = 0;
	while (s2 && s2[len])
		ptr[i++] = s2[len++];
	return (free(*s1), (*s1) = NULL, ptr);
}
