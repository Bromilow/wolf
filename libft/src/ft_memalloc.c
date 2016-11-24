/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbromilo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 09:14:03 by rbromilo          #+#    #+#             */
/*   Updated: 2016/11/24 09:23:47 by rbromilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void			*res;
	unsigned char	*res2;

	res = malloc(size);
	res2 = res;
	if (res == NULL)
		return (NULL);
	while (size--)
		*(res2++) = 0;
	return ((void *)res);
}
