/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_mng_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourkan <hbourkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 17:36:27 by hbourkan          #+#    #+#             */
/*   Updated: 2021/12/20 18:19:02 by hbourkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	open_pipes(t_struct *s, int **pipefd)
{
	int	i;

	i = 0;
	while (i < s->pipe_nb)
	{
		if (pipe(*pipefd + i * 2) == -1)
		{
			perror("Failed to pipe");
			exit(1);
		}
		i++;
	}
}

void	close_pipes(t_struct *s, int **pipefd)
{
	int	i;

	i = 0;
	while (i < s->pipe_nb * 2)
	{
		if (close((*pipefd)[i++]) == -1)
		{
			perror("Close failed");
			exit(1);
		}
	}
}

void	in_out_red(int input, int output)
{
	if (dup2(input, 0) == -1)
	{
		perror("Dup failed");
		exit(1);
	}
	if (dup2(output, 1) == -1)
	{
		perror("Dup failed");
		exit(1);
	}
}

void	in_out_red_doc(int input, int output)
{
	if (dup2(input, 0) == -1)
	{
		perror("Dup failed");
		exit(1);
	}
	if (close(input) == -1)
	{
		perror("Close failed");
		exit(1);
	}
	if (dup2(output, 1) == -1)
	{
		perror("Dup failed");
		exit(1);
	}
	if (close(output) == -1)
	{
		perror("Close failed");
		exit(1);
	}
}

void	redirec(t_struct *s, t_list *l, int **pipefd, int i)
{
	if (i == 0)
		in_out_red(s->fd, (*pipefd)[i + 1]);
	else if (l->next == NULL)
		in_out_red((*pipefd)[i - 2], s->fd2);
	else
		in_out_red((*pipefd)[i - 2], (*pipefd)[i + 1]);
}
