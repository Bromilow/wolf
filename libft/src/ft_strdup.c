/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbromilo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 09:16:30 by rbromilo          #+#    #+#             */
/*   Updated: 2016/11/24 09:16:30 by rbromilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	unsigned int		len;
	unsigned int		i;
	char				*str;

	i = 0;
	len = ft_strlen(s);
	str = (char *)malloc(sizeof(len + 1));
	while (s[i] != '\0')
	{
		str[i] = s[i];
		i++;
	}
	str[len] = '\0';
	return (str);
}
