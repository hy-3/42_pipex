/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:57:25 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/05/30 18:27:33 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(int *p, char **args, char *input_file, char *path_env)
{
	int		fd;
	char	*cmd_path;

	close(p[0]);
	if (dup2(p[1], 1) == -1)
		cust_perror("Error");
	fd = open(input_file, O_RDONLY);
	if (dup2(fd, 0) == -1)
		cust_perror("Error");
	close(fd);
	cmd_path = is_cmd_exist_and_executable(path_env, args[0]);
	execve(cmd_path, args, NULL);
	free(cmd_path);
}

void	second_child(int *p, char **args, char *output_file, char *path_env)
{
	int		fd;
	char	*cmd_path;

	close(p[1]);
	if (dup2(p[0], 0) == -1)
		cust_perror("Error");
	fd = open(output_file, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (dup2(fd, 1) == -1)
		cust_perror("Error");
	close(fd);
	cmd_path = is_cmd_exist_and_executable(path_env, args[0]);
	execve(cmd_path, args, NULL);
	free(cmd_path);
}

void	exec_first_cmd(char *argv[], int *p, char *path_env)
{
	char	*args[ARG_MAX];
	char	**cmd;
	int		arg_num;
	int		pid;

	arg_num = count_num_of_strings(argv[2], ' ');
	if (arg_num == 0)
		cust_write("Error(first_cmd): Please provide a command.\n");
	cmd = ft_split(argv[2], ' ');
	args[arg_num] = NULL;
	while (0 <= --arg_num)
		args[arg_num] = cmd[arg_num];
	pid = fork();
	if (pid < 0)
		cust_perror("Error(first_cmd)");
	if (pid == 0)
		first_child(p, args, argv[1], path_env);
	if (waitpid(-1, NULL, 0) == -1)
		cust_perror("Error(first_cmd)");
	cust_free(cmd);
	free(cmd);
}

void	exec_second_cmd(char *argv[], int *p, char *path_env)
{
	char	*args[ARG_MAX];
	char	**cmd;
	int		arg_num;
	int		pid;

	arg_num = count_num_of_strings(argv[3], ' ');
	if (arg_num == 0)
		cust_write("Error(second_cmd): Please provide a command.\n");
	cmd = ft_split(argv[3], ' ');
	args[arg_num] = NULL;
	while (0 <= --arg_num)
		args[arg_num] = cmd[arg_num];
	pid = fork();
	if (pid < 0)
		cust_perror("Error(second_cmd)");
	if (pid == 0)
		second_child(p, args, argv[4], path_env);
	close(p[0]);
	close(p[1]);
	if (waitpid(-1, NULL, 0) == -1)
		cust_perror("Error(second_cmd)");
	cust_free(cmd);
	free(cmd);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		p[2];
	char	*path_env;

	if (argc == 5)
	{
		is_file_exist_and_readable(argv[1]);
		path_env = get_path_env(envp);
		if (pipe(p) < 0)
			cust_perror("Error");
		exec_first_cmd(argv, p, path_env);
		exec_second_cmd(argv, p, path_env);
	}
	else
		cust_write("Error: Give 4 args (input, cmd1, cmd2, output)\n");
	return (0);
}
