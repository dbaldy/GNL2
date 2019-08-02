/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 13:41:50 by dbaldy            #+#    #+#             */
/*   Updated: 2016/02/11 13:35:31 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

t_lc				*list_clear(t_lc **begin, int fd)
{
	t_lc	*buf;
	t_lc	*temp;

	buf = *begin;
	temp = buf->next;
	if (buf->fno == fd)
	{
		*begin = (*begin)->next;
		free((buf)->str);
		free(buf);
	}
	while (temp)
	{
		if (temp->fno == fd)
		{
			free(temp->str);
			buf->next = temp->next;
			temp->next = NULL;
			free(temp);
		}
		buf = buf->next;
		temp = temp->next;
	}
	return (NULL);
}

t_lc				*scan(int fd, int type)
{
	static t_lc		*lc_begin;
	t_lc			*temp;
	t_lc			*new;

	temp = lc_begin;
	if (type == DESTROY_LC)
		return (list_clear(&lc_begin, fd));
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
	new->str = ft_strdup(EMPTY_STRING);
	return (new);
}

static int			ft_check(t_lc *obj, char **res)
{
	int		size;
	char		*temp;

	if (ft_strchr(obj->str, '\n') != NULL)
	{
		size = ft_strchr(obj->str, '\n') - obj->str;
		*res = ft_strsub(obj->str, 0, size);
		temp = ft_strdup(ft_strchr(obj->str, '\n') + 1);
		free(obj->str);
		obj->str = temp;
		return (LINE_READ);
	}
	*res = obj->str;
	return (NO_NL);
}

static int			read_line(t_lc *obj, char *buf, char **line)
{
	int		size;
	char		*temp;

	while ((size = read(obj->fno, buf, BUFF_SIZE)) > 0)
	{
		buf[size] = '\0';	
		temp = ft_strjoin(obj->str, buf);
		free(obj->str);
		obj->str = temp;
		if (ft_check(obj, line) == LINE_READ)
			break ;
	}
	if (size == 0)
	{
		scan(obj->fno, DESTROY_LC);
		return (END_O_F);
	}
	return (LINE_READ);
}

int					get_next_line(int const fd, char **line)
{
	t_lc		*obj;
	char		*buf;
	int			ret;

	if ((line == NULL) || (obj = scan(fd, GET_LC)) == NULL)
		return (ERROR_CODE);
	if (ft_check(obj, line) == LINE_READ)
		return (LINE_READ);
	if ((buf = (char*)malloc((sizeof(char) + 1) * (BUFF_SIZE + 1))) == NULL)
		return (ERROR_CODE);
	ret = read_line(obj, buf, line);
	free(buf);
	return (ret);
}
