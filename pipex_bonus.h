/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtretiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:19:43 by gtretiak          #+#    #+#             */
/*   Updated: 2025/03/28 18:31:42 by gtretiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include "libft.h"
# include <errno.h>

typedef struct s_pipex
{
	int		argc;
	int		check_infile;
	int		check_lim;
	int		num_cmd;
	int		infile;
	int		outfile;
	int		*pid;
	int		**fd;
	char	**av;
	char	**env;
}	t_pipex;

# define ERR_ARG "Invalid number of arguments\n"
# define ERR_CREAT "File creating error\n"
# define ERR_OPEN "File openning error\n"
# define ERR_WRITE "File writting error\n"
# define ERR_REDIR "Redirection error\n"
# define ERR_MALLOC "Malloc error\n"
# define ERR_FORK "Fork error\n"

// Settings
void	ft_init_pipex(int argc, char **av, char **env, t_pipex *pipex);
void	ft_piping(t_pipex *pipex);
int		ft_get_num_cmd(t_pipex *pipex);
void	ft_malloc_pipex(t_pipex *pipex);
void	ft_forking(t_pipex *pipex);

// Handling files
int		ft_get_infile(t_pipex *pipex);
void	ft_read_from_user(t_pipex *pipex);
void	ft_write_to_tmp(char *line);
int		ft_get_outfile(t_pipex *pipex);
void	ft_remove_tmp(t_pipex *pipex);

// Child processes
void	ft_run_child(t_pipex *pipex, int i);
void	ft_execute_first(t_pipex *pipex);
void	ft_execute_middle(t_pipex *pipex, int i);
void	ft_execute_last(t_pipex *pipex);

// Process related
void	ft_one_cmd(t_pipex *pipex);
void	ft_run_single(t_pipex *pipex);
void	ft_redirection(t_pipex *pipex);
void	ft_run_parent(t_pipex *pipex);

// Executing itself
char	**ft_find_paths(char **env);
char	*ft_get_path(char *cmd, char **env);
void	ft_execute(char *arg, t_pipex *pipex);

// Checking stuff and handling errors
void	ft_check_files(char *input, char *output, t_pipex *pipex);
void	ft_check_output(char *output);
void	ft_handle_special_error(char *error, int exit_code);
int		ft_handle_error(int code, char *name);

// Cleaning up
void	ft_clean_up(t_pipex *pipex, char **args);
void	ft_free_split(char **arr, int code);
void	ft_free_array(int **arr, int code, t_pipex *pipex);

#endif
