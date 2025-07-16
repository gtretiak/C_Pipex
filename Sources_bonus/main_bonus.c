/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtretiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 22:31:12 by gtretiak          #+#    #+#             */
/*   Updated: 2025/03/31 12:03:01 by gtretiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **av, char **env)
{
	t_pipex	pipex;

	ft_init_pipex(argc, av, env, &pipex);
	if (argc < 3 || (argc < 4 && !ft_strncmp(av[1], "here_doc", 8)))
		ft_handle_special_error(ERR_ARG, 1);
	ft_check_files(av[1], av[argc - 1], &pipex); // infile (here_doc) and outfile checking
	if (pipex.check_infile == 1 && argc < 4) // infile is invalid and there aren´t enough arguments
		return (1);
	ft_piping(&pipex);
	ft_forking(&pipex);
	ft_run_parent(&pipex);
	if (pipex.pid)
		free(pipex.pid);
	if (pipex.fd)
		ft_free_array(pipex.fd, 0, &pipex);
	return (0);
}
