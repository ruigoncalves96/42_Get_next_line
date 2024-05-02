/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 22:55:53 by randrade          #+#    #+#             */
/*   Updated: 2024/05/02 18:18:01 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	char	*str;

	str = malloc(BUFFER_SIZE + 1);
	if (str == NULL)
		return (NULL);

	return (str);
}

int	main(void)
{
	int	fd;

	fd = open("text.txt", O_RDONLY);

	get_next_line(fd);
	//print

	close(fd);
	return (0);
}
