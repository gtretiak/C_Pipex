/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtretiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:42:30 by gtretiak          #+#    #+#             */
/*   Updated: 2025/03/30 14:44:06 by gtretiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **av, char **env)
{
	int	fd[2];
	int	pid;
	int	check;

	if (argc < 3 || argc > 5)
		ft_handle_arg_error();
	check = ft_check_files(av[1], av[argc - 1]);
	if (check >= 1 && argc < 5)
		return (1);
	if (check == 2)
		check--;
	if (pipe(fd) == -1)
		exit(2);
	pid = fork();
	if (pid == -1)
		exit(2);
	if (pid == 0)
	{
		ft_run_child(argc - check, av + check, env, fd);
		return (0);
	}
	else
		ft_run_parent(argc, av, env, fd);
	return (0);
}
/*	if (argc < 5)
		ft_handle_error(argc, av[argc - 1]);*/
