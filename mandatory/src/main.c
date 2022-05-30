/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:57:25 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/05/30 16:02:43 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(int *p, char **args, char *input_file)
{
	int	fd;

	close(p[0]);
	if (dup2(p[1], 1) == -1)
		cust_perror("Error");
	fd = open(input_file, O_RDONLY);
	if (dup2(fd, 0) == -1)
		cust_perror("Error");
	close(fd);
	execve(is_cmd_exist_and_executable(args[0]), args, NULL);
}

void	second_child(int *p, char **args, char *output_file)
{
	int	fd;

	close(p[1]);
	if (dup2(p[0], 0) == -1)
		cust_perror("Error");
	fd = open(output_file, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (dup2(fd, 1) == -1)
		cust_perror("Error");
	close(fd);
	execve(is_cmd_exist_and_executable(args[0]), args, NULL);
}

void	exec_first_cmd(char *argv[], int *p)
{
	char	*args[ARG_MAX];
	char	**cmd;
	int		arg_num;
	int		pid;

	arg_num = count_num_of_strings(argv[2], ' ');
	if (arg_num == 0)
		cust_write("Error: Please provide a command.\n");
	cmd = ft_split(argv[2], ' ');
	args[arg_num] = NULL;
	while (0 <= --arg_num)
		args[arg_num] = cmd[arg_num];
	pid = fork();
	if (pid < 0)
		cust_perror("Error");
	if (pid == 0)
		first_child(p, args, argv[1]);
}

void	exec_second_cmd(char *argv[], int *p)
{
	char	*args[ARG_MAX];
	char	**cmd;
	int		arg_num;
	int		pid;

	arg_num = count_num_of_strings(argv[3], ' ');
	if (arg_num == 0)
		cust_write("Error: Please provide a command.\n");
	cmd = ft_split(argv[3], ' ');
	args[arg_num] = NULL;
	while (0 <= --arg_num)
		args[arg_num] = cmd[arg_num];
	pid = fork();
	if (pid < 0)
		cust_perror("Error");
	if (pid == 0)
		second_child(p, args, argv[4]);
}

void	check_cmd_path(char	**envp)
{
	char	*path;
	int		i;
	int		arg_num;

	path = NULL;
	i = 0;
	while (envp[i])
	{
		path = ft_strnstr(envp[i++], "PATH=", 5);
		if (path != NULL)
			break;
	}
	if (path == NULL)
		cust_write("Error: PATH env can't be found from envirnment variables");
	path += 5;
    printf("%s\n", path);
	
	arg_num = count_num_of_strings(path + 5, ':');
	if (arg_num == 0)
		cust_write("Error: nothing set on PATH env.\n");
	cmd = ft_split(path + 5, ':');

}

int	main(int argc, char *argv[], char *envp[])
{
	int	p[2];

	check_cmd_path(envp);

	if (argc == 5)
	{
		is_file_exist_and_readable(argv[1]);
		if (pipe(p) < 0)
			cust_perror("Error");
		exec_first_cmd(argv, p);
		if (waitpid(-1, NULL, 0) == -1)
			cust_perror("Error");
		exec_second_cmd(argv, p);
		close(p[0]);
		close(p[1]);
		if (waitpid(-1, NULL, 0) == -1)
			cust_perror("Error");
	}
	else
		cust_write("Error: Give 4 args (input, cmd1, cmd2, output)\n");
	return (0);
}

//TODO: change to take a pth from envirnment