/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourkan <hbourkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 10:23:59 by hbourkan          #+#    #+#             */
/*   Updated: 2021/12/21 12:19:28 by hbourkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# define BUFFER_SIZE 1

typedef struct s_struct
{
	int		childpid;
	int		fd;
	int		fd2;
	int		pipe_nb;
	char	**envp;
}	t_struct;

typedef struct s_list
{
	char			*path;
	char			**cmd;
	struct s_list	*next;
}	t_list;

typedef struct s_doc
{
	int		childpid;
	int		childpid2;
	int		fd;
	int		pipefd[2];
	char	**envp;
	char	*path;
	char	*path2;
	char	**cmd;
	char	**cmd2;
}	t_doc;

char	*full_cmdpath(char **envp, char *argv);
void	check_cmd(char *path, char *path2);
void	check_cmd2(char *path);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin2(char const *s1, char const *s2);
char	*ft_strndup(char const *s1, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	**treat_env(char **envp);
void	open_pipes(t_struct *s, int **pipefd);
void	close_pipes(t_struct *s, int **pipefd);
void	in_out_red(int input, int output);
void	in_out_red_doc(int input, int output);
void	redirec(t_struct *s, t_list *l, int **pipefd, int i);
t_list	*ft_lstnew(char **cmd, char *path);
void	ft_lstadd_back(t_list **alst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstclear(t_list **lst, void (del)(void*));
char	**treat_env(char **envp);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	pipex_heredoc(int argc, char **argv, char **envp, t_doc *p);
void	process_doc(t_doc *p, char *argv, char **envp);
void	free_all(t_struct *p);
void	free_all2(t_doc *p);
char	*get_next_line(int fd);
char	*with_newline(char **storage);
char	*no_newline(char **storage);
void	loop(char **storage, char **buffer, int fd);
char	*ft_strdup(char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strchr(const char *s, int c);
#endif