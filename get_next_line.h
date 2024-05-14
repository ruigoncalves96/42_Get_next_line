/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 22:59:44 by randrade          #+#    #+#             */
/*   Updated: 2024/05/14 17:49:19 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
#include <stdio.h> // DELETE INCLUDE !!!!!!!!!!!

# ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
# endif

typedef struct s_list
{
	char		*str;
	struct s_list	*next;
}			t_list;

char	*get_next_line(int fd);
int	ft_check_nl(char *str);
int	ft_strlen(char *str);
size_t	ft_strlcpy(char *dst, char *src, size_t size);
char    *ft_strjoin(char *s1, char *s2);

#endif
