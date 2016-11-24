/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbromilo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 09:17:04 by rbromilo          #+#    #+#             */
/*   Updated: 2016/11/24 09:17:05 by rbromilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(dest);
	while ((src[i] != '\0') && (i < n))
	{
		dest[len + i] = src[i];
		i++;
	}
	if (i < n)
		while (i < n)
		{
			dest[len + i] = '\0';
			i++;
		}
	else
		dest[len + ++i] = '\0';
	return (dest);
}
