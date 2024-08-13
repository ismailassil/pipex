/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 09:40:30 by iassil            #+#    #+#             */
/*   Updated: 2024/01/01 21:33:21 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_header/pipex.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	size_start;

	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	size_start = ft_strlen(s + start);
	if (size_start < len)
		len = size_start;
	ptr = ft_calloc(len + 1, sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s + start, len + 1);
	return (ptr);
}

char	*ft_strchr(char *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if (*str == (char)c)
		return ((char *)str);
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	size_t	len;
	size_t	start;
	size_t	end;
	char	*ptr;

	start = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	len = ft_strlen(s1);
	end = len - 1;
	while (start < len && ft_strchr(set, s1[start]))
		start++;
	while (end > 0 && ft_strchr(set, s1[end]))
		end--;
	if (start > end)
		return (ft_strdup(""));
	else
		end = end - start + 1;
	ptr = ft_substr(s1, start, end);
	if (ptr == NULL)
		return (NULL);
	return (ptr);
}
