/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtretiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:31:11 by gtretiak          #+#    #+#             */
/*   Updated: 2025/03/30 13:52:52 by gtretiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include "libft.h"
# include <errno.h>

void	ft_handle_arg_error(void);
int		ft_handle_error(int code, char *name);
int		ft_check_files(char *input, char *output);
void	ft_free_split(char **arr, int code);
void	ft_run_child(int argc, char **av, char **env, int *fd);
void	ft_run_parent(int argc, char **av, char **env, int *fd);
void	ft_redirection(char **av, int argc);
char	**ft_find_paths(char **env);
char	*ft_get_path(char *cmd, char **env);
void	ft_execute(char *arg, char **env);

#endif
