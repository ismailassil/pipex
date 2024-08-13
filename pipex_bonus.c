/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 19:27:39 by iassil            #+#    #+#             */
/*   Updated: 2024/08/13 07:14:05 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./_header/pipex_bonus.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	ft_putstr(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write(fd, &str[i], 1);
		i++;
	}
}

void	ft_multi_pipes(t_fd fd, char **av, char **env)
{
	int		pipefd[2];
	int		i;
	int		id;

	i = fd.index_cmd;
	while (fd.index_cmd < (fd.arg_count - 1))
	{
		if (pipe(pipefd) == -1)
			(perror("pipe"), exit(EXIT_FAILURE));
		id = fork();
		if (id == -1)
			(perror("fork"), exit(EXIT_FAILURE));
		if (id == 0)
			ft_child_process(pipefd, av, env, fd);
		else
			(close(pipefd[1]), close(fd.infile), fd.infile = pipefd[0]);
		fd.index_cmd++;
	}
	while (i++ < (fd.arg_count - 1))
		wait(NULL);
}

int	main(int ac, char **av, char **env)
{
	t_fd	fd;

	fd.arg_count = ac;
	ft_check_open_file(av, ac, &fd);
	if (ac >= 5)
		ft_multi_pipes(fd, av, env);
	else
		(perror("Too Few Arguments"), exit(EXIT_FAILURE));
	return (0);
}
