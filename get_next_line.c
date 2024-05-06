/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 22:55:53 by randrade          #+#    #+#             */
/*   Updated: 2024/05/06 13:50:29 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char	*check_new_line(char *str)
{
}

static char	*get_line(char *str)
{
}

static t_list	*read_buffer(t_list *head, int fd)
{
	t_list	*new_line;

	new_line = malloc(sizeof(t_list));
	if (new_line == NULL)
		return (NULL);
	new_line->str = malloc(BUFFER_SIZE);
	read(fd, new_line->str, BUFFER_SIZE);
	new_line->str[BUFFER_SIZE + 1] = '\0';
	return (new_line);
}

char	*get_next_line(int fd)
{
}

int	main(void)
{
	int	fd;
	t_list	*new_line;

	fd = open("text.txt", O_RDONLY);

	new_line = read_buffer(fd);
	printf("%s\n", new_line->str);

	free(new_line->str);
	free(new_line);
	close(fd);
	return (0);
}
