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

	close(fd[0]); // read end (we don´t need it, so we close it)
	dup2(fd[1], 1); // we duplicate write end to STDOUT
	close(fd[1]); //now stdout becomes fd[1]
	if (argc > 3)
	{
		infile = open(av[1], O_RDONLY);
		if (infile == -1)
			infile = open("/dev/null", O_RDONLY); // to avoid crashing we use dev/null if the infile can´t be opened
		if (infile != -1) // otherwise we redirect STDIN to infile (now we read from the file, not the terminal)
		{
			dup2(infile, 0);
			close(infile);
		}
		ft_execute(av[2], env); // actual command execution
	}
	return ;
}

void	ft_run_parent(int argc, char **av, char **env, int *fd)
{
	int	outfile;

	close(fd[1]); // This time we close write end
	dup2(fd[0], 0); // and duplicate read end to STDIN
	close(fd[0]); // now STDIN becomes fd[0]
	outfile = open(av[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644); // we open outfile in truncate mode (or just create it)
	if (outfile != -1)
	{
		dup2(outfile, 1); // now STDOUT becomes the outfile
		close(outfile);
	}
	else
		exit(2); // if cannot open it
	if (argc > 3)
		ft_execute(av[argc - 2], env);
	else
		ft_redirection(av, argc); // if just three arguments we redirect from the infile
	wait(NULL); // waiting for the child process to finish
}

void	ft_redirection(char **av, int argc)
{
	char	buf[4096]; // for reading
	int		i;
	int		infile;

	infile = open(av[1], O_RDONLY); 
	if (infile == -1) // if infile cannot be opened exit
	{
		close(1);
		exit(2);
	}
	while (1)
	{
		if (argc == 3) // reading from the infile
			i = read(infile, buf, sizeof(buf));
		else // reading from STDIN
			i = read(0, buf, sizeof(buf));
		if (i <= 0)
			break ;
		if (write(1, buf, i) == -1) // writing to stdout, namely the outfile here
			ft_putstr_fd("Error writing to outfile\n", 2);
	}
	close(infile);
	close(1); //closing the outfile
}
