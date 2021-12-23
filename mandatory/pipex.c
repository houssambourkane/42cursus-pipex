/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourkan <hbourkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:16:39 by hbourkan          #+#    #+#             */
/*   Updated: 2021/12/20 23:49:27 by hbourkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process(t_struct *p, char **envp)
{
	if (pipe(p->pipefd) == -1)
	{
		perror("Failed to pipe");
		exit(1);
	}
	children_processes(p, envp);
	close(p->pipefd[0]);
	close(p->pipefd[1]);
	if (wait(NULL) == -1)
	{
		perror("Wait failed");
		exit(1);
	}
	if (wait(NULL) == -1)
	{
		perror("Wait failed");
		exit(1);
	}
}

void	pipex(int argc, char **argv, char **envp, t_struct *p)
{
	p->envp = treat_env(envp);
	if (!p->envp)
	{
		perror("Command not found");
		exit(127);
	}
	p->cmd = ft_split(argv[2], ' ');
	p->cmd2 = ft_split(argv[3], ' ');
	p->path = full_cmdpath(p->envp, argv[2]);
	p->path2 = full_cmdpath(p->envp, argv[3]);
	check_cmd(p->path, p->path2);
	p->fd = open(argv[1], O_RDONLY);
	if ((p->fd) == -1)
	{
		perror("Open failed");
		exit(1);
	}
	p->fd2 = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if ((p->fd2) == -1)
	{
		perror("Open failed");
		exit(1);
	}
	process(p, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_struct	pipi;

	if (argc == 5)
	{
		pipex(argc, argv, envp, &pipi);
		free_all(&pipi);
	}
	else
		return (0);
}
