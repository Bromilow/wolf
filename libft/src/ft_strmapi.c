/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbromilo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 09:17:01 by rbromilo          #+#    #+#             */
/*   Updated: 2016/11/24 09:17:02 by rbromilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char			*new_str;
	unsigned int	i;

	new_str = NULL;
	i = 0;
	if (s)
		new_str = (char *)malloc(ft_strlen(s) + 1);
	if (!new_str || !s)
		return (NULL);
	while (s[i] != '\0')
	{
		new_str[i] = f(i, s[i]);
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
