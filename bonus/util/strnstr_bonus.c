/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:44:53 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/05/30 17:44:56 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/pipex_bonus.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	k;

	i = 0;
	if (haystack == needle)
		return ((char *)haystack);
	if (*needle == '\0')
		if (len == 0 || haystack[i] == '\0')
			return ((char *)&haystack[i]);
	while (haystack[i] != '\0' && i < len)
	{
		k = 0;
		while (haystack[i] == needle[k] && haystack[i] != '\0' && i < len)
		{
			k++;
			i++;
		}
		if (needle[k] == '\0')
			return ((char *)(&haystack[i - k]));
		i -= (k - 1);
	}
	return (NULL);
}
