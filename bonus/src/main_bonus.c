/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:57:25 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/05/30 12:53:38 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec_first_cmd(char *argv[], int *p1, int pid, int fd)
{
	char	*args[ARG_MAX];
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

void	exec_middle_cmd(char *str, int *p1, int *p2, int pid, int fd)
{
	char	*args[ARG_MAX];
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
}

void	exec_last_cmd(char *str, char *file, int *p1, int pid, int fd, int argc)
{
	char	*args[ARG_MAX];
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
		dup2(p1[0], 0);
		fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0777);
		dup2(fd, 1);
		close(fd);
		execve(path, args, NULL);
	}
}

int	main(int argc, char *argv[])
{
	int	p[ARG_MAX][2]; 
	int	pid;
	int	fd;
	int	i;
	int	k;

	if (argc >= 5)
	{
		is_file_exist_and_readable(argv[1]);
		if (pipe(p[0]) < 0)
			cust_perror("Error");
		exec_first_cmd(argv, p[0], pid, fd);
		if (waitpid(-1, NULL, 0) == -1)
			cust_perror("Error");
		argc -= 2;
		i = 3;
		k = 0;
		while (i < argc)
		{
			if (pipe(p[k + 1]) < 0)
				cust_perror("Error");
			exec_middle_cmd(argv[i], p[k], p[k + 1], pid, fd);
			close(p[k][0]);
			close(p[k][1]);
			if (waitpid(-1, NULL, 0) == -1)
				cust_perror("Error");
			i++;
			k++;
		}
		exec_last_cmd(argv[argc], argv[argc + 1], p[k], pid, fd, argc);
		close(p[k][0]);
		close(p[k][1]);
		if (waitpid(-1, NULL, 0) == -1)
			cust_perror("Error");
	}
	else
		cust_write("Error: Give at least 4 args \n");
	return (0);
}
