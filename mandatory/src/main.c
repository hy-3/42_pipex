/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:57:25 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/05/30 11:37:03 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_first_cmd(char *argv[], int *p, int pid, int fd)
{
	char	*args[100]; // char	*args[ARG_MAX];
	char	**cmd;
	int		arg_num;
	char	*path;

	arg_num = count_num_of_strings(argv[2]);
	if (arg_num == 0)
		cust_write("Error: Please provide a command.\n");
	cmd = cust_split(argv[2]);
	args[arg_num] = NULL;
	while (0 <= --arg_num)
		args[arg_num] = cmd[arg_num];
	path = is_cmd_exist_and_executable(args[0]);
	pid = fork();
	if (pid < 0)
		cust_perror("Error");
	if (pid == 0)
	{
		close(p[0]);
		dup2(p[1], 1);
		fd = open(argv[1], O_RDONLY);
		dup2(fd, 0);
		close(fd);
		execve(path, args, NULL);
	}
}

void	exec_second_cmd(char *argv[], int *p, int pid, int fd)
{
	char	*args[100]; // char	*args[ARG_MAX];
	char	**cmd;
	int		arg_num;
	char	*path;

	arg_num = count_num_of_strings(argv[3]);
	if (arg_num == 0)
		cust_write("Error: Please provide a command.\n");
	cmd = cust_split(argv[3]);
	args[arg_num] = NULL;
	while (0 <= --arg_num)
		args[arg_num] = cmd[arg_num];
	path = is_cmd_exist_and_executable(args[0]);
	pid = fork();
	if (pid < 0)
		cust_perror("Error");
	if (pid == 0)
	{
		close(p[1]);
		dup2(p[0], 0);
		fd = open(argv[4], O_CREAT | O_TRUNC | O_WRONLY, 0777);
		dup2(fd, 1);
		close(fd);
		execve(path, args, NULL);
	}
}

int	main(int argc, char *argv[])
{
	int	p[2];
	int	pid;
	int	fd;

	if (argc == 5)
	{
		is_file_exist_and_readable(argv[1]);
		if (pipe(p) < 0)
			cust_perror("Error");
		exec_first_cmd(argv, p, pid, fd);
		if (waitpid(-1, NULL, 0) == -1)
			cust_perror("Error");
		exec_second_cmd(argv, p, pid, fd);
		close(p[0]);
		close(p[1]);
		if (waitpid(-1, NULL, 0) == -1)
			cust_perror("Error");
	}
	else
		cust_write("Error: Give 4 args (input, cmd1, cmd2, output)\n");
	return (0);
}
