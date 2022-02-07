/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolee <yolee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 01:50:09 by yolee             #+#    #+#             */
/*   Updated: 2022/02/07 17:35:02 by yolee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"get_next_line_bonus.h"

t_fd_list	*buffer_allocate(t_fd_list **fd_list, int fd)
{
	t_fd_list	*curr;

	curr = (*fd_list);
	while (curr != NULL)
	{
		if (curr->fd == fd)
			return (curr);
		curr = curr->next;
	}
	if (!ft_lstadd(fd_list, fd))
		return (NULL);
	return ((*fd_list));
}

int	read_to_buffer(t_fd_list *curr, t_fd_list **fd_list, int fd)
{
	ssize_t	read_size;

	read_size = read(fd, curr->buf, BUFFER_SIZE);
	if (read_size <= 0)
	{
		if (curr == (*fd_list))
			(*fd_list) = (*fd_list)->next;
		if (curr->prev != NULL)
			curr->prev->next = curr->next;
		if (curr->next != NULL)
			curr->next->prev = curr->prev;
		free(curr->buf);
		free(curr);
		return (0);
	}
	curr->buf[read_size] = '\0';
	return (1);
}

char	*find_line_end(char *buf, int *end_flag)
{
	char	*line_end;

	line_end = ft_strchr(buf, '\n');
	if (!line_end)
		line_end = ft_strchr(buf, '\0');
	else
	{
		line_end++;
		(*end_flag) = 1;
	}
	return (line_end);
}

int	cat_line(t_fd_list *curr, char **line, size_t *line_len, int *end_flag)
{
	char	*line_end;
	char	*temp_line;

	line_end = find_line_end(curr->buf, end_flag);
	(*line_len) += (size_t)(line_end - curr->buf);
	temp_line = (*line);
	(*line) = (char *)malloc(sizeof(char) * ((*line_len) + 1));
	if ((*line) == NULL)
		return (0);
	if (!temp_line)
		(*line)[0] = '\0';
	else
	{
		ft_memmove((*line), temp_line, ft_strlen(temp_line) + 1);
		free(temp_line);
	}
	ft_strlcat((*line), curr->buf, (*line_len) + 1);
	ft_memmove(curr->buf, line_end, ft_strlen(line_end) + 1);
	return (1);
}

char	*get_next_line(int fd)
{
	static t_fd_list	*fd_list = NULL;
	t_fd_list			*curr;
	char				*line;
	int					end_flag;
	size_t				line_len;

	line = NULL;
	line_len = 0;
	end_flag = 0;
	if (BUFFER_SIZE <= 0)
		return (NULL);
	curr = buffer_allocate(&fd_list, fd);
	if (curr == NULL)
		return (NULL);
	while (!end_flag)
	{
		if (!ft_strlen(curr->buf))
			if (!read_to_buffer(curr, &fd_list, fd))
				break ;
		if (!cat_line(curr, &line, &line_len, &end_flag))
			return (NULL);
	}
	return (line);
}
