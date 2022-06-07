/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:34:16 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/06/07 16:28:12 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/pipex.h"

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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((unsigned char) *s1 != '\0' && (unsigned char) *s2 != '\0' && n > 0)
	{
		if ((unsigned char) *s1 != (unsigned char) *s2)
			return ((unsigned char) *s1 - (unsigned char) *s2);
		s1++;
		s2++;
		n--;
	}
	if (n > 0)
		return ((unsigned char) *s1 - (unsigned char) *s2);
	return (0);
}
