/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourkan <hbourkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 18:58:13 by hbourkan          #+#    #+#             */
/*   Updated: 2021/12/16 14:44:26 by hbourkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(s);
	while (i <= j)
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}

char	*no_newline(char **storage)
{
	char	*line;
	char	*temp;

	if (**storage == '\0')
	{
		free(*storage);
		*storage = NULL;
		return (NULL);
	}
	temp = *storage;
	line = ft_substr(*storage, 0, ft_strlen(*storage));
	free(temp);
	*storage = NULL;
	return (line);
}

char	*with_newline(char **storage)
{
	char	*line;
	char	*temp;
	int		i;

	i = ft_strchr(*storage, '\n');
	line = ft_substr(*storage, 0, i + 1);
	temp = *storage;
	*storage = ft_substr(*storage, i + 1, ft_strlen(*storage));
	free(temp);
	return (line);
}

void	loop(char **storage, char **buffer, int fd)
{
	int	i;

	i = 0;
	while (ft_strchr(*storage, '\n') == -1)
	{
		if (*buffer)
		{
			free(*buffer);
			*buffer = NULL;
		}
		*buffer = malloc(BUFFER_SIZE + 1);
		if (*buffer == NULL)
			return ;
		i = read(fd, *buffer, BUFFER_SIZE);
		if (i == 0 || i == -1)
			break ;
		(*buffer)[i] = '\0';
		*storage = ft_strjoin(*storage, *buffer);
	}
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*buffer;

	buffer = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!storage)
	{
		storage = ft_strdup("");
		if (storage == NULL)
			return (NULL);
	}
	loop(&storage, &buffer, fd);
	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}
	if (ft_strchr(storage, '\n') == -1)
		return (no_newline(&storage));
	return (with_newline(&storage));
}
