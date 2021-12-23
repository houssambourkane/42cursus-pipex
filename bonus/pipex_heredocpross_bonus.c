/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_heredocpross_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourkan <hbourkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 12:23:53 by hbourkan          #+#    #+#             */
/*   Updated: 2021/12/21 12:25:44 by hbourkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	pipex_heredoc(int argc, char **argv, char **envp, t_doc *p)
{
	p->envp = treat_env(envp);
	if (!p->envp)
	{
		perror("Command not found");
		exit(127);
	}
	p->cmd = ft_split(argv[3], ' ');
	p->cmd2 = ft_split(argv[4], ' ');
	p->path = full_cmdpath(p->envp, argv[3]);
	p->path2 = full_cmdpath(p->envp, argv[4]);
	check_cmd(p->path, p->path2);
	p->fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if ((p->fd) == -1)
	{
		perror("Open failed");
		exit(1);
	}
	if (pipe(p->pipefd) == -1)
	{
		perror("Failed to pipe");
		exit(1);
	}
	process_doc(p, argv[2], envp);
}
