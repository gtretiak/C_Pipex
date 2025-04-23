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

	if (pipex->check_lim == 1)
	{
		ft_read_from_user(pipex);
		file = open("tmp", O_RDONLY);
	}
	else
	{
		file = open(pipex->av[1], O_RDONLY);
		if (file == -1)
			file = open("/dev/null", O_RDONLY);
	}
	return (file);
}

int	ft_get_outfile(t_pipex *pipex)
{
	int	file;

	if (pipex->check_lim == 1)
		file = open(pipex->av[pipex->argc - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		file = open(pipex->av[pipex->argc - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (file);
}

void	ft_read_from_user(t_pipex *pipex)
{
	char	*line;
	int		i;

	while (1)
	{
		i = 0;
		while (i++ < pipex->num_cmd - 1)
			ft_putstr_fd("pipe ", 1);
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0, 2);
		if (line == NULL)
			break ;
		if (!ft_strncmp(line, pipex->av[2], ft_strlen(pipex->av[2]))
			&& line[ft_strlen(pipex->av[2])] == '\n')
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

	file = open("tmp", O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (file == -1)
		ft_handle_special_error(ERR_CREAT, 1);
	written = write(file, line, ft_strlen(line));
	if (written == -1)
		ft_handle_special_error(ERR_WRITE, 1);
	close(file);
}

void	ft_remove_tmp(t_pipex *pipex)
{
	if (!ft_strncmp(pipex->av[1], "here_doc", 8))
		unlink("./tmp");
}
