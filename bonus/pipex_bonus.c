/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourkan <hbourkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:13:36 by hbourkan          #+#    #+#             */
/*   Updated: 2021/12/21 12:08:10 by hbourkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child_process(t_struct *s, t_list *l, int **pipefd, char **envp)
{
	int	i;

	i = 0;
	while (l)
	{
		s->childpid = fork();
		if (s->childpid == 0)
		{
			redirec(s, l, pipefd, i);
			close_pipes(s, pipefd);
			if (execve(l->path, l->cmd, envp) == -1)
			{
				perror("Couldn't exec");
				exit(1);
			}
		}
		else if (s->childpid == -1)
		{
			perror("Fork failed");
			exit(1);
		}
		l = l->next;
		i += 2;
	}
}

void	process(t_struct *s, t_list *l, char **envp)
{
	int	*pipefd;
	int	i;

	i = 0;
	pipefd = malloc(sizeof(int) * (s->pipe_nb * 2));
	if (!pipefd)
		return ;
	open_pipes(s, &pipefd);
	child_process(s, l, &pipefd, envp);
	close_pipes(s, &pipefd);
	while (i < s->pipe_nb)
	{
		wait(NULL);
		i++;
	}
	free(pipefd);
}

void	cmd_gathering(int argc, char **argv, char **envp, t_struct *ptr)
{
	t_list	*list_command;
	t_list	*new_element;
	int		i;

	i = 2;
	list_command = ft_lstnew(ft_split(argv[i], ' '),
			full_cmdpath(ptr->envp, argv[i]));
	check_cmd2(list_command->path);
	i++;
	while (i < argc - 1)
	{
		new_element = ft_lstnew(ft_split(argv[i], ' '),
				full_cmdpath(ptr->envp, argv[i]));
		check_cmd2(new_element->path);
		ft_lstadd_back(&list_command, new_element);
		i++;
	}
	process(ptr, list_command, envp);
	ft_lstclear(&list_command, free);
}

void	pipex(int argc, char **argv, char **envp, t_struct *p)
{
	p->pipe_nb = argc - 4;
	p->envp = treat_env(envp);
	if (!p->envp)
	{
		perror("Command not found");
		exit(127);
	}
	p->fd = open(argv[1], O_RDONLY);
	if (p->fd == -1)
	{
		perror("Open failed");
		exit(1);
	}
	p->fd2 = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (p->fd2 == -1)
	{
		perror("Open failed");
		exit(1);
	}
	cmd_gathering(argc, argv, envp, p);
}

int	main(int argc, char **argv, char **envp)
{
	t_struct	pipi;
	t_doc		pipi_doc;

	if (argc > 4)
	{
		if (ft_strnstr(argv[1], "here_doc", 8))
		{
			if (argc == 6)
			{
				pipex_heredoc(argc, argv, envp, &pipi_doc);
				free_all2(&pipi_doc);
			}
		}
		else
		{
			pipex(argc, argv, envp, &pipi);
			free_all(&pipi);
		}
	}
	else
		return (0);
}
