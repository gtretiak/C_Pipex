/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtretiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 22:31:34 by gtretiak          #+#    #+#             */
/*   Updated: 2025/03/28 18:31:22 by gtretiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_clean_up(t_pipex *pipex, char **args)
{
	if (pipex->pid)
		free(pipex->pid);
	if (pipex->fd)
		ft_free_array(pipex->fd, 0, pipex);
	ft_free_split(args, 1);
}

void	ft_execute(char *arg, t_pipex *pipex)
{
	char	**cmd_with_args;
	char	*path;

	cmd_with_args = ft_split(arg, ' ');
	if (cmd_with_args[0] == NULL)
		ft_free_split(cmd_with_args, 1);
	if (access(cmd_with_args[0], F_OK) != 0
		|| ft_strncmp(cmd_with_args[0], "/", 1))
		path = ft_get_path(cmd_with_args[0], pipex->env);
	else
		path = cmd_with_args[0];
	if (!path)
		ft_clean_up(pipex, cmd_with_args);
	if (pipex->check_infile > 0 && pipex->num_cmd < 2)
		unlink(pipex->av[pipex->argc - 1]);
	if (pipex->check_lim)
		unlink("./tmp");
	if (execve(path, cmd_with_args, pipex->env) == -1)
	{
		if (path != cmd_with_args[0])
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
