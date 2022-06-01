/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:57:25 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/06/01 18:46:22 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(t_param *param, char **exec_args)
{
	int		fd;
	char	*cmd_path;

	if (close(param->p[0]) == -1)
		cust_perror("Error(first_child: close p[0])");
	if (dup2(param->p[1], 1) == -1)
		cust_perror("Error(first_child: dup2 p[1])");
	fd = open(param->argv[1], O_RDONLY);
	if (fd == -1)
		cust_perror("Error(first_child: open fd)");
	if (dup2(fd, 0) == -1)
		cust_perror("Error(first_child: dep2 fd)");
	if (close(fd) == -1)
		cust_perror("Error(first_child: close fd)");
	cmd_path = is_cmd_exist_and_executable(param->pathenv, exec_args[0]);
	if (execve(cmd_path, exec_args, param->envp) == -1)
		exit(127);
	free(cmd_path);
}

void	second_child(t_param *param, char **exec_args)
{
	int		fd;
	char	*cmd_path;

	if (close(param->p[1]) == -1)
		cust_perror("Error(second_child: close p[1])");
	if (dup2(param->p[0], 0) == -1)
		cust_perror("Error(second_child: dup2 p[0])");
	fd = open(param->argv[4], O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (fd == -1)
		cust_perror("Error(second_child: open fd)");
	if (dup2(fd, 1) == -1)
		cust_perror("Error(second_child: dup2 fd)");
	if (close(fd) == -1)
		cust_perror("Error(second_child: close fd)");
	cmd_path = is_cmd_exist_and_executable(param->pathenv, exec_args[0]);
	if (execve(cmd_path, exec_args, param->envp) == -1)
		exit(127);
	free(cmd_path);
}

void	exec_first_cmd(t_param *param)
{
	t_cmd_param	cmd_p;

	cmd_p.n = count_num_of_strings(param->argv[2], ' ');
	cmd_p.cmd_with_option = ft_split(param->argv[2], ' ');
	cmd_p.exec_args[cmd_p.n] = NULL;
	while (0 <= --cmd_p.n)
		cmd_p.exec_args[cmd_p.n] = cmd_p.cmd_with_option[cmd_p.n];
	cmd_p.pid = fork();
	if (cmd_p.pid < 0)
		cust_perror("Error(first_cmd: fork)");
	if (cmd_p.pid == 0)
		first_child(param, cmd_p.exec_args);
	cust_free(cmd_p.cmd_with_option);
	free(cmd_p.cmd_with_option);
}

int	exec_second_cmd(t_param *param)
{
	t_cmd_param	cmd_p;

	cmd_p.n = count_num_of_strings(param->argv[3], ' ');
	cmd_p.cmd_with_option = ft_split(param->argv[3], ' ');
	cmd_p.exec_args[cmd_p.n] = NULL;
	while (0 <= --cmd_p.n)
		cmd_p.exec_args[cmd_p.n] = cmd_p.cmd_with_option[cmd_p.n];
	cmd_p.pid = fork();
	if (cmd_p.pid < 0)
		cust_perror("Error(second_cmd: fork)");
	if (cmd_p.pid == 0)
		second_child(param, cmd_p.exec_args);
	if (!((close(param->p[0]) == 0) && (close(param->p[1]) == 0)))
		cust_perror("Error(second_cmd: close p[0] or p[1])");
	if (waitpid(cmd_p.pid, &cmd_p.status, 0) == -1)
		cust_perror("Error(second_cmd: waitpid)");
	if (wait(NULL) == -1)
		cust_perror("Error(second_cmd: wait)");
	cust_free(cmd_p.cmd_with_option);
	free(cmd_p.cmd_with_option);
	if (WIFEXITED(cmd_p.status))
		return (WEXITSTATUS(cmd_p.status));
	else
		return (WSTOPSIG(cmd_p.status));
}

int	main(int argc, char *argv[], char *envp[])
{
	t_param	param;
	int		status;

	status = 0;
	param.argv = argv;
	param.envp = envp;
	if (!envp)
		exit(1);
	if (argc == 5)
	{
		if (access(argv[1], F_OK) != 0 || access(argv[1], R_OK) != 0)
			perror("Error(main: input file check)");
		param.pathenv = get_value_of_pathenv(envp);
		if (pipe(param.p) < 0)
			cust_perror("Error(main: pipe)");
		exec_first_cmd(&param);
		status = exec_second_cmd(&param);
	}
	else
		cust_write("Error(main): Give 4 args (input, cmd1, cmd2, output)\n");
	return (status);
}
