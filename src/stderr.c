/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stderr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:58:01 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/06/07 16:44:11 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/pipex.h"

void	cust_perror(char *str, int status)
{
	perror(str);
	exit(status);
}

void	cust_write(char *str, int status)
{
	int	n;

	n = ft_strlen(str);
	write(2, str, n);
	exit(status);
}
