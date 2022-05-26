/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:57:25 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/05/26 14:57:31 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec_first_cmd(char *argv[], int *p1, int pid, int fd)
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
		close(p1[0]);
		dup2(p1[1], 1);
		fd = open(argv[1], O_RDONLY);
		dup2(fd, 0);
		close(fd);
		execve(path, args, NULL);
	}
}

void	exec_odd_cmd(char *str, int *p1, int *p2, int pid, int fd)
{
	char	*args[100]; // char	*args[ARG_MAX];
	char	**cmd;
	int		arg_num;
	char	*path;

	arg_num = count_num_of_strings(str);
	if (arg_num == 0)
		cust_write("Error: Please provide a command.\n");
	cmd = cust_split(str);
	args[arg_num] = NULL;
	while (0 <= --arg_num)
		args[arg_num] = cmd[arg_num];
	path = is_cmd_exist_and_executable(args[0]);
	pid = fork();
	if (pid < 0)
		cust_perror("Error");
	if (pid == 0)
	{
		close(p1[1]);
		close(p2[0]);
		dup2(p1[0], 0);
		dup2(p2[1], 1);
		execve(path, args, NULL);
	}
	printf("odddddd\n");
}

void	exec_even_cmd(char *str, int *p1, int *p2, int pid, int fd)
{
	char	*args[100]; // char	*args[ARG_MAX];
	char	**cmd;
	int		arg_num;
	char	*path;

	arg_num = count_num_of_strings(str);
	if (arg_num == 0)
		cust_write("Error: Please provide a command.\n");
	cmd = cust_split(str);
	args[arg_num] = NULL;
	while (0 <= --arg_num)
		args[arg_num] = cmd[arg_num];
	path = is_cmd_exist_and_executable(args[0]);
	pid = fork();
	if (pid < 0)
		cust_perror("Error");
	if (pid == 0)
	{
		close(p2[1]);
		close(p1[0]);
		dup2(p1[1], 1);
		dup2(p2[0], 0);
		execve(path, args, NULL);
	}
	printf("evennnn\n");
}

void	exec_last_cmd(char *str, char *file, int *p1, int *p2, int pid, int fd, int argc)
{
	char	*args[100]; // char	*args[ARG_MAX];
	char	**cmd;
	int		arg_num;
	char	*path;

	arg_num = count_num_of_strings(str);
	if (arg_num == 0)
		cust_write("Error: Please provide a command.\n");
	cmd = cust_split(str);
	args[arg_num] = NULL;
	while (0 <= --arg_num)
		args[arg_num] = cmd[arg_num];
	path = is_cmd_exist_and_executable(args[0]);
	pid = fork();
	if (pid < 0)
		cust_perror("Error");
	if (pid == 0)
	{
		if (argc % 2 != 0)
		{
			close(p1[1]);
			close(p2[0]);
			close(p2[1]);
			dup2(p1[0], 0);
		}
		else
		{
			close(p2[1]);
			close(p1[0]);
			close(p1[1]);
			dup2(p2[0], 0);
		}
		fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0777);
		dup2(fd, 1);
		close(fd);
		execve(path, args, NULL);
	}
}

int	main(int argc, char *argv[])
{
	int	p1[2];
	int p2[2];
	int	pid;
	int	fd;

	if (argc >= 5)
	{
		is_file_exist_and_readable(argv[1]);
		if (pipe(p1) < 0)
			cust_perror("Error");
		if (pipe(p2) < 0)
			cust_perror("Error");
		exec_first_cmd(argv, p1, pid, fd);
		if (waitpid(-1, NULL, 0) == -1)
			cust_perror("Error");
		argc -= 2;
		int i = 3;
		while (i < argc)
		{
			printf("i:%i\n",i);
			if (i % 2 != 0)
			{
				printf("be odd\n");
				exec_odd_cmd(argv[i], p1, p2, pid, fd);
				printf("af odd\n");
				close(p1[0]);
				close(p1[1]);
				close(p2[0]);
				close(p2[1]);
				if (waitpid(-1, NULL, 0) == -1)
					cust_perror("Error");
			}
			else
			{
				printf("be even\n");
				exec_even_cmd(argv[i], p1, p2, pid, fd);
				printf("af even\n");
				close(p1[0]);
				close(p1[1]);
				close(p2[0]);
				close(p2[1]);
				if (waitpid(-1, NULL, 0) == -1)
					cust_perror("Error");
			}
			i++;
		}
		printf("be last\n");
		exec_last_cmd(argv[argc], argv[argc + 1], p1, p2, pid, fd, argc);
		printf("af last\n");
		close(p1[0]);
		close(p1[1]);
		close(p2[0]);
		close(p2[1]);
		if (waitpid(-1, NULL, 0) == -1)
			cust_perror("Error");
	}
	else
		cust_write("Error: Give at least 4 args \n");
	return (0);
}
