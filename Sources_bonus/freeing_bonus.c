/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtretiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:15:15 by gtretiak          #+#    #+#             */
/*   Updated: 2025/03/28 16:15:17 by gtretiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free_split(char **arr, int code)
{
	int	i;

	i = 0;
	if (!arr && code == 1)
		exit(2);
	else if (!arr && code == 0)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	if (code == 1)
		exit(2);
}

void	ft_free_array(int **arr, int code, t_pipex *pipex)
{
	int	i;

	i = 0;
	if (!arr && code == 1)
		exit(2);
	else if (!arr && code == 0)
		return ;
	while (i < pipex->num_cmd - 1)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	if (code == 1)
		exit(2);
}
