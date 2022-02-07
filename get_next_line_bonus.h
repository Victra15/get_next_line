/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolee <yolee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 01:49:36 by yolee             #+#    #+#             */
/*   Updated: 2022/02/07 17:33:45 by yolee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_fd_list
{
	struct s_fd_list	*next;
	struct s_fd_list	*prev;
	char				*buf;
	int					fd;
}t_fd_list;

t_fd_list	*buffer_allocate(t_fd_list **fd_list, int fd);
int			read_to_buffer(t_fd_list *curr, t_fd_list **fd_list, int fd);
char		*find_line_end(char *buf, int *end_flag);
int			cat_line(t_fd_list *curr,
				char **line,
				size_t *line_len,
				int *end_flag);
char		*get_next_line(int fd);
size_t		ft_strlen(const char *str);
char		*ft_strchr(const char *s, int c);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
void		*ft_memmove(void *dst, const void *src, size_t len);
int			ft_lstadd(t_fd_list **fd_list, int fd);
#endif
