/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_free_errors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtretiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:33:15 by gtretiak          #+#    #+#             */
/*   Updated: 2025/03/30 14:39:49 by gtretiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_check_files(char *input, char *output)
{
	int	check;

	check = 0;
	if (access(input, R_OK) == -1) 
	{
		if (access(input, F_OK) == -1)
		{
			ft_handle_error(6, input); // no such file
			check = 1;
		}
		else
		{
			ft_handle_error(7, input); // access denied
			check = 2;
		}
	}
	if (access(output, F_OK) == 0) // if the output file exists
	{
		if (access(output, W_OK) == -1)
			check = ft_handle_error(7, output);
	}
	if (check == 100) // if no permission to write
		exit(2);
	return (check);
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
		return (100);
	}
	else if (code == 8)
	{
		ft_putstr_fd("zsh: command not found: ", 2);
		ft_putstr_fd(name, 2);
		write(2, "\n", 1);
	}
	return (0);
}

void	ft_handle_arg_error(void)
{
	ft_putstr_fd("Invalid number of arguments\n", 2);
	exit(2);
}

void	ft_free_split(char **arr, int code)
{
	int	i;
	int	l;

	i = 0;
	l = 1;
	if (!arr)
		return ;
	if (!arr[0])
		l = 0;
	while (arr[l])
		l++;
	while (i <= l)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	if (code == 1)
		exit(2);
}
