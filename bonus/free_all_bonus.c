/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourkan <hbourkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 17:03:26 by hbourkan          #+#    #+#             */
/*   Updated: 2021/12/20 18:34:56 by hbourkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_all(t_struct *p)
{
	int	i;

	i = 0;
	if (close(p->fd) == -1)
	{
		perror("");
		exit(1);
	}
	if (close(p->fd2) == -1)
	{
		perror("");
		exit(1);
	}
	while (p->envp[i])
		free(p->envp[i++]);
}

void	free_all2(t_doc *p)
{
	int	i;

	i = 0;
	if (close(p->fd) == -1)
	{
		perror("Close failed");
		exit(1);
	}
	while (p->envp[i])
		free(p->envp[i++]);
	i = 0;
	while (p->cmd[i])
		free(p->cmd[i++]);
	i = 0;
	while (p->cmd2[i])
		free(p->cmd2[i++]);
	free(p->path);
	free(p->path2);
}
