/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 22:55:53 by randrade          #+#    #+#             */
/*   Updated: 2024/05/02 23:20:37 by randrade         ###   ########.fr       */
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

static char	*read_full_buffer(int fd)
{
	char	*str;

	str = malloc(BUFFER_SIZE + 1);
	if (str == NULL)
		return (NULL);
	read(fd, str, BUFFER_SIZE);
	str[BUFFER_SIZE + 1] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
}

int	main(void)
{
	int	fd;
	char	*str;

	fd = open("text.txt", O_RDONLY);

	str = get_next_line(fd);
	printf("%s\n", str);

	free(str);
	close(fd);
	return (0);
}
