/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolee <yolee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 01:50:09 by yolee             #+#    #+#             */
/*   Updated: 2022/01/28 15:36:15 by yolee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"get_next_line.h"

int	read_to_buffer(char *buf, int fd, int *end_flag)
{
	ssize_t		read_size;

	read_size = read(fd, buf, BUFFER_SIZE - 1);
	if (read_size <= 0)
	{
		free(buf);
		*end_flag = 1;
		return (0);
	}
	buf[read_size] = '\0';
	return (1);
}

int	cat_line(char *buf, char *line, size_t line_size, int *end_flag)
{
	char	*temp_line;
	char	*line_end;

	line_end = ft_strchr(buf, '\n');
	if (!line_end)
		line_end = ft_strchr(buf, '\0');
	else
	{
		*end_flag = 1;
		line_end++;
	}
	line_size += (size_t)(line_end - buf);
	temp_line = line;
	line = malloc(sizeof(char) * line_size);
	if (line == NULL)
		return (0);
	if (temp_line != NULL)
		line = ft_memmove(line, temp_line, line_size);
	else
		line[0] = '\0';
	ft_strlcat(line, buf, line_size);
	ft_memmove(buf, line_end, ft_strlen(line_end));
	free(temp_line);
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*buf = NULL;
	char		*line;
	int			end_flag;
	size_t		line_size;

	line = NULL;
	if (buf == NULL)
	{
		buf = malloc(sizeof(char) * BUFFER_SIZE);
		if (buf == NULL)
			return (NULL);
	}
	line_size = 0;
	end_flag = 0;
	while (!end_flag)
	{
		if (!ft_strlen(buf))
			if (!read_to_buffer(buf, fd, &end_flag))
				return (NULL);
		if (!cat_line(buf, line, line_size, &end_flag))
			return (NULL);
	}
	return (line);
}
