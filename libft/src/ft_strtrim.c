/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbromilo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 09:18:42 by rbromilo          #+#    #+#             */
/*   Updated: 2016/11/24 09:18:43 by rbromilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char			*new_str;
	unsigned int	start;
	unsigned int	end;
	unsigned int	i;

	i = 0;
	start = 0;
	end = ft_strlen(s) - 1;
	while (s[start] == ' ' || s[start] == '\n' || s[start] == '\t')
		start++;
	while (s[end] == ' ' || s[end] == '\n' || s[end] == '\t')
		end--;
	new_str = (char *)malloc((end - start) + 1);
	while (start <= end)
		new_str[i++] = s[start++];
	new_str[++i] = '\0';
	return (new_str);
}
