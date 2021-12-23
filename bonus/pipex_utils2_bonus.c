/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourkan <hbourkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 10:21:42 by hbourkan          #+#    #+#             */
/*   Updated: 2021/12/20 18:49:35 by hbourkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

t_list	*ft_lstnew(char **cmd, char *path)
{
	t_list	*new_element;

	new_element = malloc(sizeof(t_list));
	if (new_element == NULL)
		return (NULL);
	new_element->cmd = cmd;
	new_element->path = path;
	new_element->next = NULL;
	return (new_element);
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*last;

	if (*alst == NULL)
	{
		*alst = new;
		(*alst)->next = NULL;
		return ;
	}
	last = ft_lstlast(*alst);
	last->next = new;
}

t_list	*ft_lstlast(t_list *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}

void	ft_lstclear(t_list **lst, void (del)(void*))
{	
	t_list	*temp;
	int		i;

	if (!(*lst))
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		del((*lst)->path);
		i = 0;
		while ((*lst)->cmd[i])
			del((*lst)->cmd[i++]);
		free((*lst)->cmd);
		free(*lst);
		*lst = temp;
	}
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (((unsigned char)s1[i] || (unsigned char)s2[i]) && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
