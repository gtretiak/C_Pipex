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

	cmd_with_args = ft_split(arg, ' '); // "ls -l" becomes ["ls", "-l", NULL]
	if (cmd_with_args[0] == NULL) // cleanup if the command is empty 
		ft_free_split(cmd_with_args, 1);
	if (access(cmd_with_args[0], F_OK) != 0 // if it exists...
		|| ft_strncmp(cmd_with_args[0], "/", 1)) // ... and starts with / which means it´s absolute path, we can use it directly
		path = ft_get_path(cmd_with_args[0], env); // otherwise we try look for it
	else
		path = cmd_with_args[0];
	if (!path) // invalid path, so cleanup
		ft_free_split(cmd_with_args, 1); 
	if (execve(path, cmd_with_args, env) == -1) // if execve fails, cleaning up
	{
		if (access(cmd_with_args[0], F_OK) != 0) // if path was malloced
			free(path);
		ft_free_split(cmd_with_args, 1);
	}
}

char	**ft_find_paths(char **env)
{
	int		i;
	char	**paths;

	i = 0;
	while (env[i]) // iterating through the env list
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			break ;
		i++;
	}
	if (!env[i]) // the end of the list with no PATH=
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
	paths = ft_find_paths(env); // retrieving the list of PATH directories
	while (paths[i]) // iterating through the list of PATHs
	{
		prepath = ft_strjoin(paths[i++], "/"); // joining /
		pathname = ft_strjoin(prepath, cmd); // joining cmd
		free(prepath);
		if (access(pathname, F_OK) == 0) // we return the constructed path exists if it exists
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
