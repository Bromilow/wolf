/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbromilo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 09:14:09 by rbromilo          #+#    #+#             */
/*   Updated: 2016/11/24 09:14:10 by rbromilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*dest2;
	unsigned char	*src2;

	dest2 = (unsigned char *)dest;
	src2 = (unsigned char *)src;
	while (n--)
	{
		*(dest2++) = *(src2);
		if (*(src2++) == (unsigned char)c)
			return (dest2);
	}
	return (NULL);
}
