/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _process_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 13:34:18 by iassil            #+#    #+#             */
/*   Updated: 2024/01/11 21:32:52 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_header/pipex.h"

void	ft_f(char **str)
{
	size_t	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	(free(str), str = NULL);
}

char	*ft_trim_path(char **path, char *cmd)
{
	size_t	i;
	char	*path_holder;
	char	*return_path;

	i = -1;
	path_holder = NULL;
	while (path[++i] != 0)
	{
		path_holder = ft_strjoin(path[i], "/");
		if (path_holder == NULL)
			(free(path_holder), path_holder = NULL, exit(EXIT_FAILURE));
		return_path = ft_strjoin(path_holder, cmd);
		if (return_path == NULL)
			(free(return_path), return_path = NULL,
				free(path_holder), path_holder = NULL,
				exit(EXIT_FAILURE));
		(free(path_holder), path_holder = NULL);
		if (access(return_path, F_OK | X_OK) == 0)
		{
			ft_f(path);
			return (return_path);
		}
	}
	return (NULL);
}

char	*ft_check_path(char **cmd, char **env)
{
	char	**path;
	char	*envp_path;
	char	*return_path;

	while (*env)
	{
		envp_path = ft_strnstr(*env, "PATH=", 5);
		env++;
		if (envp_path != NULL)
			break ;
	}
	if (envp_path == NULL)
		(perror("path"), exit(EXIT_FAILURE));
	return_path = ft_strtrim(envp_path, "PATH=");
	if (return_path == NULL)
		(exit(EXIT_FAILURE));
	path = ft_split(return_path, ':');
	if (path == NULL)
		(ft_f(path), exit(EXIT_FAILURE));
	(free(return_path), return_path = NULL);
	envp_path = ft_trim_path(path, cmd[0]);
	if (!envp_path)
		(ft_f(path), perror("Command not found"), exit(EXIT_FAILURE));
	return (envp_path);
}
