/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbromilo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 09:13:15 by rbromilo          #+#    #+#             */
/*   Updated: 2016/11/24 09:13:16 by rbromilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*strnl(const char *buff, size_t *pos, size_t stop)
{
	size_t	len;
	size_t	offset;

	len = 0;
	offset = *pos;
	while (buff[*pos] != '\n' && *pos < stop)
	{
		*pos += 1;
		len++;
	}
	return (ft_strsub(buff, offset, len));
}

int				ft_gnl(const int fd, char **line)
{
	static size_t	pos = BUFF_SIZE;
	static ssize_t	eob = BUFF_SIZE;
	static char		buff[BUFF_SIZE];

	*line = ft_strnew(1);
	while (buff[pos] != '\n' && eob > 0)
	{
		if ((ssize_t)pos == eob)
		{
			pos = 0;
			if ((eob = read(fd, buff, BUFF_SIZE)) == -1)
				return (-1);
		}
		if ((*line = ft_strjoin(*line, strnl(buff, &pos, eob))) == NULL)
			return (-1);
	}
	if ((ssize_t)pos != eob)
		pos++;
	if (eob == 0)
	{
		pos = BUFF_SIZE;
		eob = BUFF_SIZE;
		return (0);
	}
	return (1);
}
