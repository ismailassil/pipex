/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _child_process_.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 09:31:30 by iassil            #+#    #+#             */
/*   Updated: 2024/01/13 17:44:22 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_header/pipex.h"

static void	ft_check_(char **envp_path, char ***cmd, char **env)
{
	if (access(*cmd[0], F_OK | X_OK) == 0)
		*envp_path = *cmd[0];
	else
	{
		*envp_path = ft_check_path(*cmd, env);
		if (*envp_path == NULL)
			(free(*envp_path), ft_f(*cmd), exit(EXIT_FAILURE));
	}
}

void	ft_first_child(int *pipefd, char **av, char **env)
{
	char	**f_cmd;
	char	*envp_path;
	int		fd;

	close(pipefd[0]);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		(perror(av[1]), exit(EXIT_FAILURE));
	convert_to_space(&av[2]);
	f_cmd = ft_split(av[2], ' ');
	if (f_cmd == NULL)
		return (ft_f(f_cmd), exit(EXIT_FAILURE));
	ft_check_(&envp_path, &f_cmd, env);
	if (dup2(fd, STDIN_FILENO) == -1)
		(perror("dup2 (fd)"), exit(EXIT_FAILURE));
	close(fd);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		(perror("dup2 (pipe)"), exit(EXIT_FAILURE));
	close(pipefd[1]);
	if (execve(envp_path, f_cmd, NULL) == -1)
		(ft_f(f_cmd), perror("execve"), exit(EXIT_FAILURE));
}

void	ft_second_child(int *pipefd, char **av, char **env)
{
	char	**s_cmd;
	char	*envp_path;
	int		fd;

	close(pipefd[1]);
	fd = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		(perror(av[4]), exit(EXIT_FAILURE));
	convert_to_space(&av[3]);
	s_cmd = ft_split(av[3], ' ');
	if (s_cmd == NULL)
		return (ft_f(s_cmd), exit(EXIT_FAILURE));
	ft_check_(&envp_path, &s_cmd, env);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		(perror("dup2 (pipe)"), exit(EXIT_FAILURE));
	close(pipefd[0]);
	if (dup2(fd, STDOUT_FILENO) == -1)
		(perror("dup2 (fd)"), exit(EXIT_FAILURE));
	close(fd);
	if (execve(envp_path, s_cmd, NULL) == -1)
		(ft_f(s_cmd), perror("execve"), exit(EXIT_FAILURE));
}
