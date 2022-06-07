/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:34:28 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/06/07 16:29:16 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../pipex.h"

char	*ft_strchr(const char *s, int c)
{
	char	*new_s;

	if (s == NULL)
		return (NULL);
	new_s = (char *) s;
	while (*new_s != '\0')
	{
		if (*new_s == (char) c)
			return (new_s);
		new_s++;
	}
	if (c == 0)
		return (new_s);
	else
		return (NULL);
}

size_t	ft_strlen(const char *str)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		count++;
		str++;
	}
	return (count);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	total_len;
	unsigned int	i;
	unsigned int	k;
	char			*res;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2);
	res = malloc((total_len + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	k = 0;
	i = 0;
	while (s1[i] > 0)
		res[k++] = s1[i++];
	i = 0;
	while (s2[i] > 0)
		res[k++] = s2[i++];
	res[k] = '\0';
	return (res);
}

char	*ft_strdup(const char *s1)
{
	char	*res;
	int		count;

	count = 0;
	while (s1[count] != '\0')
		count++;
	res = (char *) malloc((count + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	count = 0;
	while (s1[count] != '\0')
	{
		res[count] = s1[count];
		count++;
	}
	res[count] = '\0';
	return (res);
}
