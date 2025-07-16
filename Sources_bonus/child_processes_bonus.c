/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtretiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:56:33 by gtretiak          #+#    #+#             */
/*   Updated: 2025/03/31 12:05:12 by gtretiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_run_child(t_pipex *pipex, int i)
{
	if (i == 0)
		ft_execute_first(pipex); // redirection from STDIN to infile + first pipe
	else if (i == pipex->num_cmd - 1)
		ft_execute_last(pipex); // redirection from STDOUT to outfile + final pipe
	else
		ft_execute_middle(pipex, i); // read from the previous pipe and write to the next one
}

void	ft_execute_first(t_pipex *pipex)
{
	int	i;

	i = 1;
	close(pipex->fd[0][0]); // we are not going to read from the first pipe (only write)
	while (i < pipex->num_cmd - 1) // closing all unused pipes
	{
		close(pipex->fd[i][1]);
		close(pipex->fd[i][0]);
		i++;
	}
	if (pipex->argc - pipex->check_infile > 3)
	{
		if (pipex->infile != -1)
		{
			dup2(pipex->infile, 0); // redirection STDIN to infile
			close(pipex->infile);
		}
		dup2(pipex->fd[0][1], 1); // redirection STDOUT to the write-end of the first pipe
		close(pipex->fd[0][1]);
		ft_execute(pipex->av[2 + pipex->check_lim], pipex);
	}
	close(1);
}

void	ft_execute_middle(t_pipex *pipex, int i)
{
	int	j;

	j = 0;
	while (j < pipex->num_cmd - 1)
	{
		if (j != i - 1)
			close(pipex->fd[j][0]);
		if (j != i)
			close(pipex->fd[j][1]);
		j++;
	}
	dup2(pipex->fd[i - 1][0], 0); // redirection STDIN to the previous pipe´s read end
	dup2(pipex->fd[i][1], 1); // redirection STDOUT to the current pipe´s write end
	close(pipex->fd[i - 1][0]);
	close(pipex->fd[i][1]);
	ft_execute(pipex->av[2 + pipex->check_lim + i], pipex);
	close(0);
	close(1);
}

void	ft_execute_last(t_pipex *pipex)
{
	int	i;

	i = 0;
	close(pipex->fd[pipex->num_cmd - 2][1]);
	while (i < pipex->num_cmd - 2)
	{
		if (i != pipex->num_cmd - 2)
			close(pipex->fd[i][1]);
		if (i != pipex->num_cmd - 1)
			close(pipex->fd[i][0]);
		i++;
	}
	dup2(pipex->fd[pipex->num_cmd - 2][0], 0); // redirection STDIN to the read end of the last pipe
	close(pipex->fd[pipex->num_cmd - 2][0]);
	pipex->outfile = ft_get_outfile(pipex);
	if (pipex->outfile != -1)
	{
		dup2(pipex->outfile, 1); // redirection STDOUT to outfile
		close(pipex->outfile);
	}
	else
		exit(2);
	ft_execute(pipex->av[pipex->argc - 2], pipex);
	close(1);
	return ;
}
