/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbromilo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 09:17:21 by rbromilo          #+#    #+#             */
/*   Updated: 2016/11/24 09:18:12 by rbromilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *str, size_t n)
{
	size_t	i;

	i = 0;
	while ((str[i] != '\0') && (i < n))
	{
		dest[i] = str[i];
		i++;
	}
	if (i < n)
		while (i < n)
		{
			dest[i] = '\0';
			i++;
		}
	else
		dest[++i] = '\0';
	return (dest);
}
