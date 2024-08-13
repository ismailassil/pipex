/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 09:40:30 by iassil            #+#    #+#             */
/*   Updated: 2024/01/01 21:33:19 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_header/pipex.h"

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	t_srclen;
	size_t	i;

	i = 0;
	t_srclen = ft_strlen(src);
	if (dstsize < 1)
		return (t_srclen);
	while (src[i] != '\0' && i < (dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	return (t_srclen);
}

char	*ft_strdup(char *s1)
{
	char	*ptr;
	size_t	size;

	size = ft_strlen(s1) + 1;
	ptr = ft_calloc(size, sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s1, size);
	return (ptr);
}

char	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = (char *)malloc(count * size);
	if (!ptr)
		return (NULL);
	while (i < (count * size))
		ptr[i++] = '\0';
	return (ptr);
}

char	*ft_strnstr(char *haystack, char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	index;

	i = 0;
	if (haystack == NULL || needle == NULL || len == 0)
		return (NULL);
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		j = 0;
		index = i;
		while (haystack[index] == needle[j] && needle[j] != '\0' && index < len)
		{
			if (index > len)
				return (NULL);
			else if (needle[j + 1] == '\0')
				return ((char *)&haystack[i]);
			j++;
			index++;
		}
		i++;
	}
	return (NULL);
}
