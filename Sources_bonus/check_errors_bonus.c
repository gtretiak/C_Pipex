/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtretiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:15:25 by gtretiak          #+#    #+#             */
/*   Updated: 2025/03/31 11:54:26 by gtretiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_check_files(char *input, char *output, t_pipex *pipex)
{
	if (access(input, R_OK) == -1 && ft_strncmp(input, "here_doc", 8))
	{
		if (access(input, F_OK) == -1)
			ft_handle_error(6, input);
		else
			ft_handle_error(7, input);
		pipex->check_infile = 1;
	}
	if (!ft_strncmp(input, "here_doc", 8))
		pipex->check_lim = 1;
	ft_check_output(output);
}

void	ft_check_output(char *output)
{
	if (access(output, F_OK) == 0)
	{
		if (access(output, W_OK) == -1)
		{
			ft_handle_error(7, output);
			exit(2);
		}
	}
}

int	ft_handle_error(int code, char *name)
{
	if (code == 6)
	{
		ft_putstr_fd("zsh: no such file or directory: ", 2);
		ft_putstr_fd(name, 2);
		write(2, "\n", 1);
	}
	else if (code == 7)
	{
		ft_putstr_fd("zsh: permission denied: ", 2);
		ft_putstr_fd(name, 2);
		write(2, "\n", 1);
	}
	else if (code == 8)
	{
		usleep(1);
		ft_putstr_fd("zsh: command not found: ", 2);
		ft_putstr_fd(name, 2);
		write(2, "\n", 1);
	}
	return (0);
}

void	ft_handle_special_error(char *error, int exit_code)
{
	ft_putstr_fd(error, 2);
	if (exit_code == 1)
		exit(2);
}
