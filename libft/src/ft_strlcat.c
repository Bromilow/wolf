/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbromilo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 09:16:49 by rbromilo          #+#    #+#             */
/*   Updated: 2016/11/24 09:16:50 by rbromilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(dest);
	while ((src[i] != '\0') && (len + i <= n))
	{
		dest[len + i] = src[i];
		i++;
	}
	if (len + i <= n)
		while (len + i <= n)
		{
			dest[len + i] = '\0';
			i++;
		}
	else
		dest[len + ++i] = '\0';
	if (len < n)
		return (len + ft_strlen(src));
	else
		return (n + ft_strlen(src));
}
