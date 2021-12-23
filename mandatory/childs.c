/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourkan <hbourkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 16:16:35 by hbourkan          #+#    #+#             */
/*   Updated: 2021/12/23 10:24:33 by hbourkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child1(t_struct *p, char **envp)
{
	if (close(p->pipefd[0]) == -1)
	{
		perror("Close failed");
		exit(1);
	}
	if (dup2(p->fd, 0) == -1)
	{
		perror("Error failed");
		exit(1);
	}
	if (dup2(p->pipefd[1], 1) == -1)
	{
		perror("Dup failed");
		exit(1);
	}
	if (close(p->pipefd[1]) == -1)
	{
		perror("Close failed");
		exit(1);
	}
	if (execve(p->path, p->cmd, envp) == -1)
	{
		perror("Exec failed");
		exit(1);
	}
}

static void	child2(t_struct *p, char **envp)
{
	if (close(p->pipefd[1]) == -1)
	{
		perror("Close failed");
		exit(1);
	}
	if (dup2(p->pipefd[0], 0) == -1)
	{
		perror("Dup failed");
		exit(1);
	}
	if (close(p->pipefd[0]) == -1)
	{
		perror("Close failed");
		exit(1);
	}
	if (dup2(p->fd2, 1) == -1)
	{
		perror("Dup failed");
		exit(1);
	}
	if (execve(p->path2, p->cmd2, envp) == -1)
	{
		perror("Exec failed");
		exit(1);
	}
}

void	children_processes(t_struct *p, char **envp)
{
	p->childpid = fork();
	if (p->childpid == -1)
	{
		perror("Fork failed");
		exit(1);
	}
	else if (p->childpid == 0)
		child1(p, envp);
	p->childpid2 = fork();
	if (p->childpid2 == -1)
	{
		perror("Fork failed");
		exit(1);
	}
	else if (p->childpid2 == 0)
		child2(p, envp);
}
