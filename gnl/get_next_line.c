/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 13:41:50 by dbaldy            #+#    #+#             */
/*   Updated: 2016/02/10 19:57:56 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

t_lc				*scan(int fd)
{
	static t_lc		*lc_begin;
	t_lc			*temp;
	t_lc			*new;

	temp = lc_begin;
	while (temp)
	{
		if (temp->fno == fd)
			return (temp);
		temp = temp->next;
	}
	if ((new = (t_lc*)malloc(sizeof(t_lc))) == NULL)
		return (NULL);
	new->next = lc_begin;
	lc_begin = new;
	new->fno = fd;
	new->str = ft_strdup("");
	return (new);
}

static int			ft_check(char *temp, char **str, char **res)
{
	int			size;

	if (ft_strchr(temp, '\n') != NULL)
	{
		free(*str);
		size = ft_strlen(temp) - ft_strlen(ft_strchr(temp, '\n'));
		*str = ft_strdup(ft_strchr(temp, '\n') + 1);
		*res = ft_strsub(temp, 0, size);
		free(temp);
		return (1);
	}
	return (0);
}

int			read_line(t_lc *obj, char *buf, char **line)
{
	int			size;
	char		*temp;

	temp = NULL;
	size = BUFF_SIZE;
	while (size == BUFF_SIZE)
	{
		if ((size = read(obj->fno, buf, BUFF_SIZE)) == -1)
		{
			free(buf);
			return (-1);
		}
		if (size < BUFF_SIZE)
			ft_strclr(&buf[size]);
		if (temp != NULL)
			free(temp);
		temp = ft_strjoin(obj->str, buf);
		if (ft_check(temp, &obj->str, line) == 1)
		{
			free(buf);
			return (1);
		}
	}
	free(buf);
	return (0);
}

int					get_next_line(int const fd, char **line)
{
	t_lc		*obj;
	char		*buf;

	if ((line == NULL) || (obj = scan(fd)) == NULL)
		return (-1);
	if (ft_check(ft_strdup(obj->str), &obj->str, line) == 1)
		return (1);
	if ((buf = (char*)malloc((sizeof(char) + 1) * BUFF_SIZE)) == NULL)
		return (-1);
	return (read_line(obj, buf, line));
}
