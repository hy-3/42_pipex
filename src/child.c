/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 11:53:56 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/06/07 17:08:10 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(int *p1, t_cmd_param *cmd_p, t_param *pa)
{
	int		fd;
	char	*cmd_path;

	if (close(p1[0]) == -1)
		cust_perror("Error(first_child: close p1[0])", 1);
	if (dup2(p1[1], 1) == -1)
		cust_perror("Error(first_child: dup2 p1[1])", 1);
	fd = open(pa->argv[1], O_RDONLY);
	if (fd == -1)
		cust_perror("Error(first_child: open fd)", 1);
	if (dup2(fd, 0) == -1)
		cust_perror("Error(first_child: dep2 fd)", 1);
	if (close(fd) == -1)
		cust_perror("Error(first_child: close fd)", 1);
	cmd_path = is_cmd_exist_and_executable(pa->pathenv, cmd_p->exec_args[0]);
	if (execve(cmd_path, cmd_p->exec_args, pa->envp) == -1)
		cust_write("command not found\n", 127);
}

void	middle_child(int *p1, int *p2, t_cmd_param *cmd_p, t_param *pa)
{
	char	*cmd_path;

	if (close(p1[1]) == -1)
		cust_perror("Error(middle_child: close p1[1])", 1);
	if (close(p2[0]) == -1)
		cust_perror("Error(middle_child: close p2[0])", 1);
	if (dup2(p1[0], 0) == -1)
		cust_perror("Error(middle_child: dup2 p1[0])", 1);
	if (dup2(p2[1], 1) == -1)
		cust_perror("Error(middle_child: dup2 p2[1])", 1);
	cmd_path = is_cmd_exist_and_executable(pa->pathenv, cmd_p->exec_args[0]);
	if (execve(cmd_path, cmd_p->exec_args, pa->envp) == -1)
		cust_write("command not found\n", 127);
}

void	last_child(int *p1, t_cmd_param *cmd_p, char *output, t_param *pa)
{
	int		fd;
	char	*cmd_path;

	if (close(p1[1]) == -1)
		cust_perror("Error(last_child: close p1[1])", 1);
	if (dup2(p1[0], 0) == -1)
		cust_perror("Error(last_child: dup2 p1[0])", 1);
	fd = open(output, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (fd == -1)
		cust_perror("Error(last_child: open fd)", 1);
	if (dup2(fd, 1) == -1)
		cust_perror("Error(last_child: dup2 fd)", 1);
	if (close(fd) == -1)
		cust_perror("Error(last_child: close fd)", 1);
	cmd_path = is_cmd_exist_and_executable(pa->pathenv, cmd_p->exec_args[0]);
	if (execve(cmd_path, cmd_p->exec_args, pa->envp) == -1)
		cust_write("command not found\n", 127);
}
