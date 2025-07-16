/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtretiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 22:31:50 by gtretiak          #+#    #+#             */
/*   Updated: 2025/03/30 12:53:13 by gtretiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_one_cmd(t_pipex *pipex)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		ft_handle_special_error(ERR_FORK, 1);
	if (pid == 0)
		ft_run_single(pipex);
	else
		wait(NULL); // parent waiting for a child to finish
	exit(0);
}

void	ft_run_single(t_pipex *pipex)
{
	pipex->infile = ft_get_infile(pipex);
	if (pipex->infile != -1) 
	{
		dup2(pipex->infile, 0); // redirection input to STDIN
		close(pipex->infile);
	}
	pipex->outfile = ft_get_outfile(pipex);
	if (pipex->outfile != -1)
	{
		dup2(pipex->outfile, 1); // redirection output to STDOUT
		close(pipex->outfile);
	}
	else
		exit(2);
	ft_execute(pipex->av[2 + pipex->check_lim], pipex); // current process replacement with execution
	close(1);
}

void	ft_run_parent(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->num_cmd - 1) // parent closes all the ends since it doesn´t need them
	{
		close(pipex->fd[i][0]);
		close(pipex->fd[i][1]);
		i++;
	}
	i = 0;
	while (i < pipex->num_cmd) // then it waits for all children
	{
		waitpid(pipex->pid[i], NULL, 0);
		i++;
	}
}

void	ft_redirection(t_pipex *pipex)
{
	char	buf[4096]; // buffer to copy the content
	int		i;

	pipex->infile = ft_get_infile(pipex); // openning infile
	pipex->outfile = ft_get_outfile(pipex); // openning outfile
	if (pipex->infile == -1 || pipex->outfile == -1)
	{
		if (pipex->infile == -1)
			close(pipex->outfile);
		else
			close(pipex->infile);
		ft_handle_special_error(ERR_REDIR, 1);
	}
	while (1) // actual copying (reading, then writing)
	{
		i = read(pipex->infile, buf, sizeof(buf));
		if (i <= 0)
			break ;
		if (write(pipex->outfile, buf, i) == -1)
			ft_putstr_fd("Error writing to outfile\n", 2);
	}
	close(pipex->infile); // closing...
	close(pipex->outfile);
	ft_remove_tmp(pipex); // removind it redirection was performed from here_doc
}
