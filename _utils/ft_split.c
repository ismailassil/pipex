/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 08:27:30 by iassil            #+#    #+#             */
/*   Updated: 2024/01/01 21:33:06 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_header/pipex.h"

static char	*ft_free(char **big_ptr, size_t b_index)
{
	while (b_index--)
		free(big_ptr[b_index]);
	(free(big_ptr), big_ptr = NULL);
	return (NULL);
}

static size_t	ft_count_words(char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static char	**ft_split_words(char *str, char **big_ptr, char c)
{
	size_t	i;
	size_t	index;
	size_t	b_index;

	i = 0;
	b_index = 0;
	while (str[i] != '\0')
	{
		index = 0;
		while (str[i] == c)
			i++;
		while (str[i] != c && str[i] != '\0')
		{
			index++;
			i++;
		}
		if (index > 0)
		{
			big_ptr[b_index++] = ft_substr(str, i - index, index);
			if (big_ptr[b_index - 1] == NULL)
				return (ft_free(big_ptr, b_index - 1), NULL);
		}
	}
	big_ptr[b_index++] = NULL;
	return (big_ptr);
}

char	**ft_split(char *str, char c)
{
	char	**big_ptr;
	size_t	words;

	words = ft_count_words(str, c) + 1;
	big_ptr = (char **)malloc(words * sizeof(char *));
	if (!big_ptr)
		return (NULL);
	big_ptr = ft_split_words(str, big_ptr, c);
	return (big_ptr);
}
