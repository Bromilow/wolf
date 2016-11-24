/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbromilo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 09:15:49 by rbromilo          #+#    #+#             */
/*   Updated: 2016/11/24 09:15:52 by rbromilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, char const *src)
{
	unsigned int		i;
	unsigned int		len;

	i = 0;
	len = ft_strlen(dest) + 1;
	while (src[i] != '\0')
	{
		dest[len + i] = src[i];
		i++;
	}
	dest[len + ++i] = '\0';
	return (dest);
}
