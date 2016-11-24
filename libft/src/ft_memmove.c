/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbromilo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 09:14:27 by rbromilo          #+#    #+#             */
/*   Updated: 2016/11/24 09:14:28 by rbromilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*temp;

	temp = (unsigned char *)malloc(n + 1);
	ft_memcpy(temp, src, n);
	ft_memcpy(dest, temp, n);
	return (temp);
}
