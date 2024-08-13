/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 09:48:59 by iassil            #+#    #+#             */
/*   Updated: 2024/08/13 07:04:13 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>

typedef struct s_fd
{
	int	infile;
	int	outfile;
	int	index_cmd;
	int	arg_count;
}		t_fd;

void	ft_first_child(int *pipefd, char **av, char **env);
void	ft_second_child(int *pipefd, char **av, char **env);
char	**ft_split(char *str, char c);
char	*ft_strnstr(char *haystack, char *needle, size_t len);
char	*ft_strtrim(char *s1, char *set);
char	*ft_calloc(size_t count, size_t size);
char	*ft_strchr(char *str, int c);
char	*ft_strdup(char *s1);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_trim_path(char **path_, char *first_cmd);
char	*ft_check_path(char **first_cmd, char **env);
char	*ft_strjoin(char *s1, char *s2);
void	ft_f(char **str);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
size_t	ft_strlen(char *str);
void	convert_to_space(char **str);

#endif
