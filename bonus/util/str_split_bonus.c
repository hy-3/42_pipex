/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:58:19 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/05/26 14:58:21 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/pipex_bonus.h"

int	count_num_of_strings(char const *s)
{
	int		i;
	int		res;
	char	c;

	i = 0;
	res = 0;
	c = ' ';
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			res++;
			while (s[i++] != c && s[i] != '\0')
				continue ;
		}
		else
			i++;
	}
	return (res);
}

void	cust_free(char **res)
{
	int	i;

	i = 0;
	while (res[i] != NULL)
		free(res[i++]);
	free(res);
	res = NULL;
}

void	fill_string_in_array(char const *s, char c, char **res)
{
	int	i;
	int	k;
	int	l;
	int	start;

	i = 0;
	k = -1;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] != c && s[i] != '\0')
				i++;
			res[++k] = (char *) malloc((i - start + 1) * sizeof(char));
			if (res[k] == NULL)
				return (cust_free(res));
			l = 0;
			while ((i - start) > 0)
				res[k][l++] = s[start++];
			res[k][l] = '\0';
		}
		else
			i++;
	}
}

char	**cust_split(char const *s)
{
	int		num_of_strings;
	char	**res;

	if (s == NULL)
		return (NULL);
	num_of_strings = count_num_of_strings(s);
	res = (char **) malloc((num_of_strings + 1) * sizeof(char *));
	if (res == NULL)
		return (NULL);
	fill_string_in_array(s, ' ', res);
	res[num_of_strings] = NULL;
	return (res);
}
