/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourkan <hbourkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 12:18:48 by hbourkan          #+#    #+#             */
/*   Updated: 2021/12/21 12:14:16 by hbourkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*full_cmdpath(char **envp, char *argv)
{
	int		i;
	int		cpt;
	char	*pathname;
	char	*temp;

	i = 0;
	cpt = 0;
	if (argv[0] == '.' && argv[1] == '/')
		return (NULL);
	while (argv[cpt] != ' ')
		cpt++;
	temp = ft_strndup(argv, cpt);
	while (envp[i])
	{
		pathname = ft_strjoin2(envp[i], temp);
		if (access(pathname, F_OK) == 0)
		{
			free(temp);
			return (pathname);
		}
		free(pathname);
		i++;
	}
	free(temp);
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

void	check_cmd2(char *path)
{
	if (!path)
	{
		perror("Command not found");
		exit(127);
	}
	if (access(path, X_OK) == -1)
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

size_t	ft_strlen(const char *str)
{
	size_t	c;

	c = 0;
	while (str[c])
		c++;
	return (c);
}
