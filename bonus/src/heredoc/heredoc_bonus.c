/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:34:35 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/05/31 16:58:30 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	heredoc(char *argv[], int argc, char *limiter, char *envp[])
{
	char	*str;
	int		p1[2];
	int		p2[2];
	char	*path_env;

	if (argc != 6)
		cust_write("Error(here_doc): Args have to be 5.\n");
	if (pipe(p1) < 0)
		cust_perror("Error(here_doc)");
	if (pipe(p2) < 0)
		cust_perror("Error(here_doc)");
	while (1)
	{
		str = get_next_line(0);
		if (ft_strnstr(str, limiter, ft_strlen(limiter)) != NULL)
			break ;
		write(p1[1], str, ft_strlen(str));
	}
	path_env = get_path_env(envp);
	exec_middle_cmd(argv[3], p1, p2, path_env);
	exec_last_cmd(argv[4], argv[5], p2, path_env);
	exit (0);
}

//TODO: implement >> to output file.