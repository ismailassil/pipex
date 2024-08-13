/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 09:01:08 by iassil            #+#    #+#             */
/*   Updated: 2024/01/13 17:43:24 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_header/pipex.h"

void	convert_to_space(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] >= 9 && (*str)[i] <= 13)
			(*str)[i] = ' ';
		i++;
	}
}

static char	*ft_check(char const *s1, char const *s2)
{
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return ((char *)s2);
	else if (s2 == NULL)
		return ((char *)s1);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	s1_len;
	size_t	s2_len;
	char	*ptr;

	if (s1 == NULL || s2 == NULL)
		return (ft_check(s1, s2));
	i = 0;
	j = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ptr = (char *)malloc(s1_len + s2_len + 1);
	if (ptr == NULL)
		return (NULL);
	while (i < s1_len)
	{
		ptr[i] = s1[i];
		i++;
	}
	while (j < s2_len)
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	return (ptr);
}
