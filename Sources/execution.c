/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtretiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:43:00 by gtretiak          #+#    #+#             */
/*   Updated: 2025/03/26 21:50:32 by gtretiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_execute(char *arg, char **env)
{
	char	**cmd_with_args;
	char	*path;

	cmd_with_args = ft_split(arg, ' ');
	if (cmd_with_args[0] == NULL)
		ft_free_split(cmd_with_args, 1);
	if (access(cmd_with_args[0], F_OK) != 0
		|| ft_strncmp(cmd_with_args[0], "/", 1))
		path = ft_get_path(cmd_with_args[0], env);
	else
		path = cmd_with_args[0];
	if (!path)
		ft_free_split(cmd_with_args, 1);
	if (execve(path, cmd_with_args, env) == -1)
	{
		if (access(cmd_with_args[0], F_OK) != 0)
			free(path);
		ft_free_split(cmd_with_args, 1);
	}
}

char	**ft_find_paths(char **env)
{
	int		i;
	char	**paths;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			break ;
		i++;
	}
	if (!env[i])
		return (NULL);
	paths = ft_split(env[i] + 5, ':');
	return (paths);
}

char	*ft_get_path(char *cmd, char **env)
{
	int		i;
	char	**paths;
	char	*prepath;
	char	*pathname;

	i = 0;
	paths = ft_find_paths(env);
	while (paths[i])
	{
		prepath = ft_strjoin(paths[i++], "/");
		pathname = ft_strjoin(prepath, cmd);
		free(prepath);
		if (access(pathname, F_OK) == 0)
		{
			ft_free_split(paths, 0);
			return (pathname);
		}
		free(pathname);
	}
	ft_free_split(paths, 0);
	ft_handle_error(8, cmd);
	return (NULL);
}
