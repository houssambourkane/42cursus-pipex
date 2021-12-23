/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourkan <hbourkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:16:14 by hbourkan          #+#    #+#             */
/*   Updated: 2021/12/20 15:44:23 by hbourkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>

typedef struct s_struct
{
	int		childpid;
	int		childpid2;
	int		fd;
	int		fd2;
	int		pipefd[2];
	char	**envp;
	char	*path;
	char	*path2;
	char	**cmd;
	char	**cmd2;
}	t_struct;

char	*full_cmdpath(char **envp, char *argv);
void	check_cmd(char *path, char *path2);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	**treat_env(char **envp);
void	children_processes(t_struct *p, char **envp);
void	free_all(t_struct *p);
#endif