/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolee <yolee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 01:50:09 by yolee             #+#    #+#             */
/*   Updated: 2022/02/07 14:46:41 by yolee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"get_next_line.h"

int	buffer_allocate(char **buf)
{
	if ((*buf) == NULL)
	{
		(*buf) = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if ((*buf) == NULL)
			return (0);
		(*buf)[0] = '\0';
		return (1);
	}
	else
		return (1);
}

int	read_to_buffer(char **buf, int fd)
{
	ssize_t		read_size;

	read_size = read(fd, (*buf), BUFFER_SIZE);
	if (read_size <= 0)
	{
		free(*buf);
		(*buf) = NULL;
		return (0);
	}
	(*buf)[read_size] = '\0';
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

int	cat_line(char *buf, char **line, size_t *line_len, int *end_flag)
{
	char	*line_end;
	char	*temp_line;

	line_end = find_line_end(buf, end_flag);
	(*line_len) += (size_t)(line_end - buf);
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
	ft_strlcat((*line), buf, (*line_len) + 1);
	ft_memmove(buf, line_end, ft_strlen(line_end) + 1);
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*buf = NULL;
	char		*line;
	int			end_flag;
	size_t		line_len;

	line = NULL;
	line_len = 0;
	end_flag = 0;
	if (BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer_allocate(&buf))
		return (NULL);
	while (!end_flag)
	{
		if (!ft_strlen(buf))
			if (!read_to_buffer(&buf, fd))
				break ;
		if (!cat_line(buf, &line, &line_len, &end_flag))
			return (NULL);
	}
	return (line);
}
