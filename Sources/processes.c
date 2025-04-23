/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtretiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:40:51 by gtretiak          #+#    #+#             */
/*   Updated: 2025/03/30 14:33:35 by gtretiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_run_child(int argc, char **av, char **env, int *fd)
{
	int	infile;

	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	if (argc > 3)
	{
		infile = open(av[1], O_RDONLY);
		if (infile == -1)
			infile = open("/dev/null", O_RDONLY);
		if (infile != -1)
		{
			dup2(infile, 0);
			close(infile);
		}
		ft_execute(av[2], env);
	}
	return ;
}

void	ft_run_parent(int argc, char **av, char **env, int *fd)
{
	int	outfile;

	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	outfile = open(av[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile != -1)
	{
		dup2(outfile, 1);
		close(outfile);
	}
	else
		exit(2);
	if (argc > 3)
		ft_execute(av[argc - 2], env);
	else
		ft_redirection(av, argc);
	wait(NULL);
}

void	ft_redirection(char **av, int argc)
{
	char	buf[4096];
	int		i;
	int		infile;

	infile = open(av[1], O_RDONLY);
	if (infile == -1)
	{
		close(1);
		exit(2);
	}
	while (1)
	{
		if (argc == 3)
			i = read(infile, buf, sizeof(buf));
		else
			i = read(0, buf, sizeof(buf));
		if (i <= 0)
			break ;
		if (write(1, buf, i) == -1)
			ft_putstr_fd("Error writing to outfile\n", 2);
	}
	close(infile);
	close(1);
}
