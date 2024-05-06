/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 22:55:53 by randrade          #+#    #+#             */
/*   Updated: 2024/05/06 16:49:23 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	del(void *str)
{
	free(str);
}

void    ft_lstclear(t_list **lst, void (*del)(void *))
{
        t_list  *i;
        t_list  *temp;

        if (!lst)
                return ;
        i = *lst;
        while (i)
        {
                temp = i;
                i = i->next;
                if (del)
                        del(temp->str);
                free(temp);
        }
        *lst = NULL;
}

static char	*join_strs(t_list *head)
{
	char	*str;

	str = ft_strdup(head->str);
	head = head->next;
	while (head->next != NULL)
	{
		ft_strlcat(str, head->str, ft_strlen(str) + ft_strlen(head->str) + 1);
		head = head->next;
	}
	ft_strlcat(str, head->str, ft_strlen(str) + ft_strlen(head->str));
	return (str);
}

static t_list	*read_buffer(int fd)
{
	t_list	*new_line;

	new_line = malloc(sizeof(t_list));
	if (new_line == NULL)
		return (NULL);
	new_line->str = malloc(BUFFER_SIZE);
	if (new_line->str == NULL)
		return (NULL);
	read(fd, new_line->str, BUFFER_SIZE);
	new_line->str[BUFFER_SIZE + 1] = '\0';
	new_line->next = NULL;
	return (new_line);
}

char	*get_next_line(int fd)
{
	t_list	*head;
	t_list	*current;
	t_list	*new_line;
	char	*str;

	head = read_buffer(fd);
	current = head;
	while (ft_strchr(current->str, '\n') == NULL)
	{
		new_line = read_buffer(fd);
		current->next = new_line;
		current = new_line;
	}
	str = join_strs(head);
	ft_lstclear(&head, del);
	return (str);
}

int	main(void)
{
	int	fd;
	char	*new_line;

	fd = open("text.txt", O_RDONLY);

	new_line = get_next_line(fd);
	printf("%s", new_line);
	new_line = get_next_line(fd);
	printf("%s", new_line);
	new_line = get_next_line(fd);
	printf("%s", new_line);

	free(new_line);
	close(fd);
	return (0);
}
