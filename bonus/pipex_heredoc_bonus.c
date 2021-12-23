/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_heredoc_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourkan <hbourkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 10:27:36 by hbourkan          #+#    #+#             */
/*   Updated: 2021/12/21 12:24:15 by hbourkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	doc_prompt(int *pipe_doc, char **line, char *argv)
{
	*line = ft_strdup("");
	write(1, "here_doc>", 9);
	while (*line)
	{
		*line = get_next_line(0);
		if (ft_strncmp(*line, argv, ft_strlen(argv)) == 0)
		{
			if ((*line)[ft_strlen(argv)] == '\n')
			{
				free(*line);
				break ;
			}
		}
		write(1, "here_doc>", 9);
		write(pipe_doc[1], *line, ft_strlen(*line));
		free(*line);
	}
	if (close(pipe_doc[1]) == -1)
	{
		perror("Close failed");
		exit(1);
	}
}

static void	child1(t_doc *p, char *argv, char **envp)
{
	char	*line;
	int		pipe_doc[2];

	if (pipe(pipe_doc) == -1)
	{
		perror("Failed to pipe");
		exit(1);
	}
	if (close(p->pipefd[0]) == -1)
	{
		perror("Close failed");
		exit(1);
	}
	doc_prompt(pipe_doc, &line, argv);
	in_out_red_doc(pipe_doc[0], p->pipefd[1]);
	if (execve(p->path, p->cmd, envp) == -1)
	{
		perror("Exec failed");
		exit(1);
	}
}

static void	child2(t_doc *p, char **envp)
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
	if (dup2(p->fd, 1) == -1)
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

static void	parent(t_doc *p)
{
	if (close(p->pipefd[0]) == -1)
	{
		perror("Close failed");
		exit(1);
	}
	if (close(p->pipefd[1]) == -1)
	{
		perror("Close failed");
		exit(1);
	}
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

void	process_doc(t_doc *p, char *argv, char **envp)
{
	p->childpid = fork();
	if (p->childpid == -1)
	{
		perror("Failed to fork");
		exit(1);
	}
	else if (p->childpid == 0)
		child1(p, argv, envp);
	p->childpid2 = fork();
	if (p->childpid2 == -1)
	{
		perror("Failed to fork");
		exit(1);
	}
	else if (p->childpid2 == 0)
		child2(p, envp);
	parent(p);
}
