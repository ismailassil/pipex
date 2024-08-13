/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 19:27:39 by iassil            #+#    #+#             */
/*   Updated: 2024/01/13 17:44:28 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./_header/pipex.h"

int	main(int ac, char *av[], char **env)
{
	int		pipefd[2];
	pid_t	id[2];

	if (ac != 5)
		(perror("Too Few Arguments"), exit(EXIT_FAILURE));
	if (pipe(pipefd) == -1)
		(perror("pipe"), exit(EXIT_FAILURE));
	id[0] = fork();
	if (id[0] == -1)
		(perror("fork"), exit(EXIT_FAILURE));
	if (id[0] == 0)
		ft_first_child(pipefd, av, env);
	else
	{
		id[1] = fork();
		if (id[1] == -1)
			(perror("fork"), exit(EXIT_FAILURE));
		if (id[1] == 0)
			ft_second_child(pipefd, av, env);
		(close(pipefd[1]), close(pipefd[0]));
		(wait(NULL), wait(NULL));
	}
	return (0);
}
