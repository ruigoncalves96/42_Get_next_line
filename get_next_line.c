/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 22:55:53 by randrade          #+#    #+#             */
/*   Updated: 2024/05/08 03:54:00 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static void	format_new_head(t_list **head)
{
	t_list	*temp;
	char	*str;
	int		new_len;
	int		i;
	int		j;

	temp = *head;
	i = 0;
	while (temp->str[i] != '\n')
		i++;
	new_len = BUFFER_SIZE - i;
	str = malloc(new_len + 1);
	if (str == NULL)
		return ;
	j = 0;
	while (temp->str[i])
	{
		i++;
		str[j] = temp->str[i];
		j++;
	}
	str[j] = '\0';
	free(temp->str);
	temp->str = str;
}

static char	*join_str(t_list **head, int len_read)
{
	t_list	*current;
	char	*str;
	int	i;
	int	j;

	current = *head;
	str = malloc(len_read + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (current != NULL)
	{
		j = 0;
		while (current->str[j] != '\n' && current->str[j] != '\0')
		{
			str[i] = current->str[j];
			i++;
			j++;
		}
		if (current->str[j] == '\n')
		{
			str[i++] = '\n';
			str[i] = '\0';
		}
		current = current->next;
	}
	return (str);
}

static int	create_list(t_list **head, int fd)
{
	t_list	*new_node;
	int		read_nbr;

	read_nbr = 0;
	new_node = NULL;
	while (!ft_check_nl(new_node))
	{
		new_node = malloc(sizeof(t_list));
		if (new_node == NULL)
			return (0);
		new_node->str = malloc(BUFFER_SIZE + 1);
		if (new_node->str == NULL)
			return (0);
		read_nbr += read(fd, new_node->str, BUFFER_SIZE);
		if (read_nbr == 0)
			return (0);
		new_node->str[BUFFER_SIZE + 1] = '\0';
		new_node->next = NULL;
		ft_lstadd_back(head, new_node);
	}
	return (read_nbr);
}

char	*get_next_line(int fd)
{
	static t_list	*head;
	char		*str;
	int		len_read;

	head = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	if (head)
		format_new_head(&head);
	len_read = create_list(&head, fd);
	if (len_read == 0)
	{
		//check --v-- function
		ft_lstclear(&head);
		return (NULL);
	}
	str = join_str(&head, len_read);
	ft_lstclear(&head);
	return (str);
	// test with empty file
}

int	main(void)
{
	int	fd;
	char	*line;

	line = NULL;
	fd = open("text.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	int i = 0;
	while (i++ != 5)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
