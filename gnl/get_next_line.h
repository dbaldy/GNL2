/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 13:40:07 by dbaldy            #+#    #+#             */
/*   Updated: 2016/02/11 11:57:36 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 5 
# include <stdlib.h>
# include <unistd.h>
# define EMPTY_STRING ""
# define ERROR_CODE -1
# define END_O_F 0
# define LINE_READ 1
# define GET_LC 0
# define DESTROY_LC 1
# define NO_NL 0

typedef struct		s_gnl_list
{
	int				fno;
	char			*str;
	struct s_gnl_list	*next;
}					t_lc;

int					get_next_line(int const fd, char **line);
char				*ft_strjoin(char const *s1, char const *s2);
void				ft_strclr(char *s);
void				ft_putendl(const char *str);
char				*ft_strsub(const char *s, unsigned int debut, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *s);
size_t					ft_strlen(const char *str);
int					ft_strcmp(const char *s1, const char *s2);
#endif
