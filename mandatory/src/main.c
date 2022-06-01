/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:57:25 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/06/01 16:41:03 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char **T = NULL;

void	first_child(int *p, char **exec_args, char *input_file, char *path_env)
{
	int		fd;
	char	*cmd_path;

	if (close(p[0]) == -1)
		exit(1);
	if (dup2(p[1], 1) == -1)
		cust_perror("Error(first_child)");
	fd = open(input_file, O_RDONLY);
	if (fd == -1)
		exit(1);
	if (dup2(fd, 0) == -1)
		cust_perror("Error(first_child)");
	if (close(fd) == -1)
		exit(1);
	cmd_path = is_cmd_exist_and_executable(path_env, exec_args[0]);
	if (execve(cmd_path, exec_args, T) == -1)
		exit(127);
	free(cmd_path);
}

void	second_child(int *p, char **exec_args, char *output, char *path_env)
{
	int		fd;
	char	*cmd_path;

	if (close(p[1]) == -1)
		exit(1);
	if (dup2(p[0], 0) == -1)
		cust_perror("Error(second_child)");
	fd = open(output, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (fd == -1)
		exit(1);
	if (dup2(fd, 1) == -1)
		cust_perror("Error(second_child)");
	if (close(fd) == -1)
		exit(1);
	cmd_path = is_cmd_exist_and_executable(path_env, exec_args[0]);
	if (execve(cmd_path, exec_args, T) == -1)
		exit(127);
	free(cmd_path);
}

void	exec_first_cmd(char *argv[], int *p, char *path_env)
{
	char	*exec_args[ARG_MAX];
	char	**cmds;
	int		arg_num;
	int		pid;

	arg_num = count_num_of_strings(argv[2], ' ');
	// if (arg_num == 0)
	// 	cust_write("Error(first_cmd): Please provide a command.\n");
	cmds = ft_split(argv[2], ' ');
	exec_args[arg_num] = NULL;
	while (0 <= --arg_num)
		exec_args[arg_num] = cmds[arg_num];
	pid = fork();
	if (pid < 0)
		cust_perror("Error(first_cmd)");
	if (pid == 0)
		first_child(p, exec_args, argv[1], path_env);
	cust_free(cmds);
	free(cmds);
}

int	exec_second_cmd(char *argv[], int *p, char *path_env)
{
	char	*exec_args[ARG_MAX];
	char	**cmds;
	int		arg_num;
	int		pid;
	int		status;

	arg_num = count_num_of_strings(argv[3], ' ');
	// if (arg_num == 0)
	// 	cust_write("Error(second_cmd): Please provide a command.\n");
	cmds = ft_split(argv[3], ' ');
	exec_args[arg_num] = NULL;
	while (0 <= --arg_num)
		exec_args[arg_num] = cmds[arg_num];
	pid = fork();
	if (pid < 0)
		cust_perror("Error(second_cmd)");
	if (pid == 0)
		second_child(p, exec_args, argv[4], path_env);
	if (close(p[0]) == -1)
		exit(1);
	if (close(p[1]) == -1)
		exit(1);
	if (waitpid(pid, &status, 0) == -1)
		cust_perror("Error(second_cmd)");
	wait(NULL); //TODO search
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (WSTOPSIG(status));
	cust_free(cmds);
	free(cmds);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		p[2];
	char	*path_env;
	int		status;
	T = envp;

	status = 0;
	if (!envp)
		exit(1);
	if (argc == 5)
	{
		is_file_exist_and_readable(argv[1]);
		path_env = get_value_of_pathenv(envp);
		if (pipe(p) < 0)
			cust_perror("Error(main)");
		exec_first_cmd(argv, p, path_env);
		status = exec_second_cmd(argv, p, path_env);
	}
	else
		cust_write("Error(main): Give 4 args (input, cmd1, cmd2, output)\n");
	return (status);
}
