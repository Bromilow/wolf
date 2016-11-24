/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbromilo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 09:18:16 by rbromilo          #+#    #+#             */
/*   Updated: 2016/11/24 09:18:18 by rbromilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;

	if (needle[0] == '\0')
		return ((char *)haystack);
	i = 0;
	while ((haystack[i] != '\0') && i < n)
	{
		j = i;
		while (needle[j - i] == haystack[j])
			if (needle[++j - i] == '\0')
				return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}
