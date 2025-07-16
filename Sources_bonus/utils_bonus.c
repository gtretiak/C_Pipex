/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtretiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 22:33:27 by gtretiak          #+#    #+#             */
/*   Updated: 2025/03/31 12:05:16 by gtretiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_init_pipex(int argc, char **av, char **env, t_pipex *pipex)
{
	pipex->argc = argc;
	pipex->av = av;
	pipex->env = env;
	pipex->num_cmd = 0;
	pipex->infile = 0;
	pipex->outfile = 0;
	pipex->check_infile = 0;
	pipex->check_lim = 0;
	pipex->fd = NULL;
	pipex->pid = NULL;
}

void	ft_malloc_pipex(t_pipex *pipex)
{
	int	i;

	i = 0;
	pipex->fd = malloc(sizeof(int *) * (pipex->num_cmd - 1)); // allocating for all the pipes between commands
	if (!pipex->fd)
		ft_handle_special_error(ERR_MALLOC, 1);
	while (i < pipex->num_cmd - 1)
	{
		pipex->fd[i] = malloc(sizeof(int) * 2); // allocating for each of them (read and write ends)
		if (!pipex->fd[i])
		{
			ft_putstr_fd("Malloc error\n", 2);
			ft_free_array(pipex->fd, 1, pipex);
		}
		i++;
	}
	pipex->pid = malloc(sizeof(int) * pipex->num_cmd); // allocating to store the PID of each commands process
	if (!pipex->pid)
	{
		ft_putstr_fd("Malloc error\n", 2);
		ft_free_array(pipex->fd, 1, pipex);
	}
}

int	ft_get_num_cmd(t_pipex *pipex)
{
	return (pipex->argc - 3 - pipex->check_lim);
}

void	ft_piping(t_pipex *pipex)
{
	int	i;

	pipex->num_cmd = ft_get_num_cmd(pipex);
	if (pipex->num_cmd == 0)
	{
		ft_redirection(pipex); // pure redirection
		exit(0);
	}
	else if (pipex->num_cmd == 1)
		ft_one_cmd(pipex);
	else
	{
		ft_malloc_pipex(pipex);
		i = 0;
		while (i < pipex->num_cmd - 1)
		{
			if (pipe(pipex->fd[i]) == -1) // pipe creating
			{
				ft_putstr_fd("Pipe error\n", 2);
				free(pipex->pid);
				ft_free_array(pipex->fd, 1, pipex);
			}
			i++;
		}
	}
}

void	ft_forking(t_pipex *pipex)
{
	int	i;

	i = 0;
	pipex->infile = ft_get_infile(pipex);
	while (i < pipex->num_cmd)
	{
		pipex->pid[i] = fork(); // forking a child process for each command
		if (pipex->pid[i] == -1)
		{
			ft_putstr_fd("Fork error\n", 2);
			free(pipex->pid);
			ft_free_array(pipex->fd, 1, pipex);
		}
		if (pipex->pid[i] == 0)
		{
			ft_run_child(pipex, i);
			exit(0);
		}
		i++;
	}
}
