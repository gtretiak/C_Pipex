/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtretiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:15:54 by gtretiak          #+#    #+#             */
/*   Updated: 2025/03/30 12:54:57 by gtretiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_get_infile(t_pipex *pipex)
{
	int	file;

	if (pipex->check_lim == 1) // it´s a here_doc case
	{
		ft_read_from_user(pipex); // let´s read from the user (STDIN) until EOF, write to the "tmp" file
		file = open("tmp", O_RDONLY); // then read what we have written to it
	}
	else
	{
		file = open(pipex->av[1], O_RDONLY); // let´s open infile
		if (file == -1)
			file = open("/dev/null", O_RDONLY); // if we can´t open it, let´s read from dev/null for crashing prevention
	}
	return (file); // returning a valid file description either from the infile, tmp or dev/null
}

int	ft_get_outfile(t_pipex *pipex)
{
	int	file;

	if (pipex->check_lim == 1) // if here_doc case, let´s use APPEND mode
		file = open(pipex->av[pipex->argc - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else // otherwise TRUNCATE mode
		file = open(pipex->av[pipex->argc - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (file); // returning the file descriptor
}

void	ft_read_from_user(t_pipex *pipex)
{
	char	*line; // a pointer to each input line
	int		i;

	while (1)
	{
		i = 0;
		while (i++ < pipex->num_cmd - 1)
			ft_putstr_fd("pipe ", 1); // we print "pipe" as many times as number of pipes between commands (for nice UX)
		ft_putstr_fd("heredoc> ", 1); // displaying final "heredoc"
		line = get_next_line(0, 2); // from STDIN
		if (line == NULL) // EOF with CTRL+D
			break ;
		if (!ft_strncmp(line, pipex->av[2], ft_strlen(pipex->av[2])) // if LIMITER is inserted
			&& line[ft_strlen(pipex->av[2])] == '\n') // and the last char is \n
		{
			free(line);
			break ;
		}
		ft_write_to_tmp(line);
		free(line);
	}
}

void	ft_write_to_tmp(char *line)
{
	int		file;
	int		written;

	file = open("tmp", O_WRONLY | O_APPEND | O_CREAT, 0644); // in APPEND mode, so we can add text in every cycle
	if (file == -1)
		ft_handle_special_error(ERR_CREAT, 1);
	written = write(file, line, ft_strlen(line));
	if (written == -1)
		ft_handle_special_error(ERR_WRITE, 1);
	close(file);
}

void	ft_remove_tmp(t_pipex *pipex)
{
	if (!ft_strncmp(pipex->av[1], "here_doc", 8)) // if it´s the here_doc case at this point we need to remove the tmp file
		unlink("./tmp");
}
