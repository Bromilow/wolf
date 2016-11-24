/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbromilo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 09:17:27 by rbromilo          #+#    #+#             */
/*   Updated: 2016/11/24 09:18:15 by rbromilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*str;
	char	*str2;

	str = malloc(size);
	if (str == NULL)
		return (NULL);
	str2 = str;
	while (size--)
		*str2++ = '\0';
	return (str);
}
