/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _child_process_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 09:31:30 by iassil            #+#    #+#             */
/*   Updated: 2024/08/13 07:12:29 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_header/pipex_bonus.h"

static void	ft_pipe_to_outfile(int *pipefd, int fd)
{
	if (dup2(fd, STDOUT_FILENO) == -1)
		(perror("dup2"), exit(EXIT_FAILURE));
	(close(fd), close(pipefd[1]));
}

static void	ft_pipe_to_next_child(int *pipefd, int fd)
{
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		(perror("dup2"), exit(EXIT_FAILURE));
	(close(pipefd[1]), close(fd));
}

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

void	ft_child_process(int *pipefd, char **av, char **env, t_fd fd)
{
	char	**cmd;
	char	*envp_path;

	close(pipefd[0]);
	convert_to_space(&av[fd.index_cmd]);
	cmd = ft_split(av[fd.index_cmd], ' ');
	if (cmd == NULL)
		return (ft_f(cmd), exit(EXIT_FAILURE));
	ft_check_(&envp_path, &cmd, env);
	if (dup2(fd.infile, STDIN_FILENO) == -1)
		(perror("dup2 (pipe 'read-end')"), exit(EXIT_FAILURE));
	close(fd.infile);
	if (fd.index_cmd == (fd.arg_count - 2))
		ft_pipe_to_outfile(pipefd, fd.outfile);
	else
		ft_pipe_to_next_child(pipefd, fd.outfile);
	if (execve(envp_path, cmd, NULL) == -1)
		(ft_f(cmd), perror("execve"), exit(EXIT_FAILURE));
}

void	ft_check_open_file(char **av, int ac, t_fd *fd)
{
	if (ft_strncmp(av[1], "here_doc", 9) == 0 && ac >= 6)
	{
		fd->index_cmd = 3;
		fd->infile = ft_input_child(av);
		fd->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd->outfile == -1)
			(perror(av[ac - 1]), exit(EXIT_FAILURE));
	}
	else
	{
		fd->index_cmd = 2;
		fd->infile = open(av[1], O_RDONLY);
		if (fd->infile == -1)
			(perror(av[1]), exit(EXIT_FAILURE));
		fd->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd->outfile == -1)
			(perror(av[ac - 1]), exit(EXIT_FAILURE));
	}
}
