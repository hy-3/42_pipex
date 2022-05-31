/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:47:06 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/05/31 15:17:56 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_child(int *p1, char **args, char *input, char *path_env)
{
	int		fd;
	char	*cmd_path;

	close(p1[0]);
	if (dup2(p1[1], 1) == -1)
		cust_perror("Error(first_child)");
	fd = open(input, O_RDONLY);
	if (dup2(fd, 0) == -1)
		cust_perror("Error(first_child)");
	close(fd);
	cmd_path = is_cmd_exist_and_executable(path_env, args[0]);
	execve(cmd_path, args, NULL);
	free(cmd_path);
}

void	middle_child(int *p1, int *p2, char **args, char *path_env)
{
	char	*cmd_path;

	close(p1[1]);
	close(p2[0]);
	if (dup2(p1[0], 0) == -1)
		cust_perror("Error(middle_child)");
	if (dup2(p2[1], 1) == -1)
		cust_perror("Error(middle_child)");
	cmd_path = is_cmd_exist_and_executable(path_env, args[0]);
	execve(cmd_path, args, NULL);
	free(cmd_path);
}

void	last_child(int *p1, char **args, char *output, char *path_env)
{
	int		fd;
	char	*cmd_path;

	close(p1[1]);
	if (dup2(p1[0], 0) == -1)
		cust_perror("Error(last_child)");
	fd = open(output, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (dup2(fd, 1) == -1)
		cust_perror("Error(last_child)");
	close(fd);
	cmd_path = is_cmd_exist_and_executable(path_env, args[0]);
	execve(cmd_path, args, NULL);
	free(cmd_path);
}
