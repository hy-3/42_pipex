/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stderr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:58:01 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/06/07 16:28:16 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/pipex.h"

void	cust_perror(char *str)
{
	perror(str);
	exit(1);
}

void	cust_write(char *str)
{
	int	n;

	n = ft_strlen(str);
	write(1, str, n);
	exit(1);
}
