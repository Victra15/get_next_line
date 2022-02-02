/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolee <yolee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 01:49:57 by yolee             #+#    #+#             */
/*   Updated: 2022/01/28 17:27:04 by yolee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	idx;

	idx = 0;
	while (str[idx] != '\0')
		idx++;
	return (idx);
}

char	*ft_strchr(const char *s, int c)
{
	char	conv_c;

	conv_c = (char)c;
	while (*s != '\0')
	{
		if (*s == conv_c)
			return ((char *)(s));
		s++;
	}
	if (conv_c == '\0')
		return ((char *)(s));
	else
		return (NULL);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	base_size;
	size_t	src_size;
	size_t	loop;

	base_size = ft_strlen(dst);
	src_size = ft_strlen(src);
	loop = 0;
	if (base_size >= dstsize)
		return (dstsize + src_size);
	while (base_size + loop < dstsize - 1)
	{
		if (loop < src_size)
			dst[base_size + loop] = src[loop];
		else
			break ;
		loop++;
	}
	dst[base_size + loop] = '\0';
	return (base_size + src_size);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*conv_dst;
	const unsigned char	*conv_src;

	if (dst == NULL && src == NULL)
		return (dst);
	if (dst < src)
	{
		conv_dst = (unsigned char *)dst;
		conv_src = (const unsigned char *)src;
		while (len--)
			*(conv_dst++) = *(conv_src++);
	}
	else
	{
		conv_dst = (unsigned char *)dst + len - 1;
		conv_src = (const unsigned char *)src + len - 1;
		while (len--)
			*(conv_dst--) = *(conv_src--);
	}
	return (dst);
}
