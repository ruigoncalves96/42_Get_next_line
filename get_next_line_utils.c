/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 23:04:34 by randrade          #+#    #+#             */
/*   Updated: 2024/05/08 03:20:44 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_check_nl(t_list *new_node)
{
	int	i;

	if (new_node == NULL)
		return (0);
	i = 0;
	while (new_node->str[i])
	{
		if (new_node->str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst == NULL)
		return ;
	if (*lst)
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstclear(t_list **lst)
{
	t_list	*i;
	t_list	*temp;

	if (!lst)
		return ;
	i = *lst;
	while (i->next != NULL)
	{
		temp = i;
		i = i->next;
		free(temp->str);
		free(temp);
	}
	*lst = i;
}
