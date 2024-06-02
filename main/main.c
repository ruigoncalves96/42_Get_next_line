/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 11:12:02 by randrade          #+#    #+#             */
/*   Updated: 2024/06/02 11:17:44 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
//#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int	fd;
	char	*line;

	line = NULL;
//	fd = open("text.txt", O_RDONLY);
//	fd = open("1char.txt", O_RDONLY);
//	fd = open("nl.txt", O_RDONLY);
//	fd = open("no_nl.txt", O_RDONLY);
//	fd = open("empty.txt", O_RDONLY);
	fd = open("words.txt", O_RDONLY);
	if (fd < 0)
		return (1);

	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	while (line)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
