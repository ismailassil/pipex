/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 09:48:59 by iassil            #+#    #+#             */
/*   Updated: 2024/08/13 07:10:16 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include "../_utils_bonus/get_next_line/get_next_line_bonus.h"

typedef struct s_fd
{
	int	infile;
	int	outfile;
	int	index_cmd;
	int	arg_count;
}		t_fd;

/** for multiple pipes**/
void	ft_child_process(int *pipefd, char **av, char **env, t_fd fd);
void	ft_multi_pipes(t_fd fd, char **av, char **env);

/** for here_doc **/
int		ft_input_child(char **av);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr(char *str, int fd);

/** functions needed **/
void	ft_check_open_file(char **av, int ac, t_fd *fd);
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
