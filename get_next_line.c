/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 22:55:53 by randrade          #+#    #+#             */
/*   Updated: 2024/05/07 17:28:53 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static t_list	*create_node(int fd)
{
	t_list	*new_node;
	int	read_nbr;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
	new_node->str = malloc(BUFFER_SIZE + 1);
	if (new_node->str == NULL)
		return (NULL);
	read_nbr = read(fd, new_node->str, BUFFER_SIZE);
	if (read_nbr < 0)
		return (NULL);
	new_node->str[BUFFER_SIZE + 1] = '\0';
	new_node->next = NULL;
	return (new_node);
}

static void	create_list(t_list **head, int fd)
{
	t_list	*new_node;
	t_list	*last_node;

	new_node = NULL;
	//check '\n' in buffer read;
	//while False 
	//	read buffer and add node to last position;
	while (!ft_check_nl(new_node))
	{
		new_node = create_node(fd);
		ft_lstadd_back(head, new_node);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*head;
	t_list	*current;
	char	*str;
	
	head = NULL;
	//create list;
	create_list(&head, fd);
	while (current->next)
	{
		printf("%s", current->str);
		current = current->next;
	}
	printf("%s", current->str);
	//join nodes list into str;
	//clear all nodes besides the last;
	ft_lstclear(&head, ft_del_str);
	//save last node str after '\n';
	//return string;
	return ("TEST");
}

int	main(void)
{
	int	fd;
	char	*new_line;

	new_line = NULL;
	fd = open("text.txt", O_RDONLY);
	if (fd < 0)
		return (1);

	new_line = get_next_line(fd);

	close(fd);
	return (0);
}
