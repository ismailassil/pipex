/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 09:57:53 by iassil            #+#    #+#             */
/*   Updated: 2024/01/13 16:56:58 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 12
# endif

char	*get_next_line(int fd);
char	*ft_str_join(char **s1, char *s2);
char	*ft_c_alloc(size_t count, size_t size);
size_t	ft_str_chr(const char *str);
size_t	ft_str_len(char *str);
char	*ft_newstr(char **str);
char	*ft_new(char **str);
void	*ft_allocate_read_check(ssize_t *nbyte, int *fd, \
								char **buf, char **line);
#endif