/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 18:08:46 by dbaldy            #+#    #+#             */
/*   Updated: 2016/02/10 19:49:16 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int			main(int ac, char **arg)
{
	char	*str;
	int		fd;
	int		i;

	i = 0;
	fd = open(arg[1], O_RDONLY);
	while (get_next_line(fd, &str) > 0)
		printf("%s\n", str);
//	get_next_line(fd, &str);
//	printf("%s\n", str);
	close(fd);
	return (0);
	ac = 9;
}
