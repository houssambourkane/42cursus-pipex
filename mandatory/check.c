/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourkan <hbourkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 10:59:15 by hbourkan          #+#    #+#             */
/*   Updated: 2021/12/21 12:12:58 by hbourkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*full_cmdpath(char **envp, char *argv)
{
	int		i;
	char	*pathname;

	i = 0;
	if (argv[0] == '.' && argv[1] == '/')
		return (NULL);
	while (argv[i] != ' ')
		i++;
	argv[i] = '\0';
	i = 0;
	while (envp[i])
	{
		pathname = ft_strjoin(envp[i], argv);
		if (access(pathname, F_OK) == 0)
			return (pathname);
		free(pathname);
		i++;
	}
	return (NULL);
}

void	check_cmd(char *path, char *path2)
{
	if (!path || !path2)
	{
		perror("Command not found");
		exit(127);
	}
	if (access(path, X_OK) == -1 || access(path2, X_OK) == -1)
	{
		perror("Permission denied");
		exit(1);
	}
}

char	**treat_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			return (ft_split((envp[i] + 5), ':'));
		i++;
	}
	return (NULL);
}

void	free_all(t_struct *p)
{
	int	i;

	i = 0;
	if (close(p->fd) == -1)
	{
		perror("Close failed");
		exit(1);
	}
	if (close(p->fd2) == -1)
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
