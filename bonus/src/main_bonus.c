/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:57:25 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/05/31 17:50:50 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec_first_cmd(char *argv[], int *p1, char *path_env)
{
	char	*args[ARG_MAX];
	char	**cmd;
	int		arg_num;
	int		pid;

	is_file_exist_and_readable(argv[1]);
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
		first_child(p1, args, argv[1], path_env);
	if (waitpid(-1, NULL, 0) == -1)
		cust_perror("Error(first_cmd)");
	cust_free(cmd);
	free(cmd);
}

void	exec_middle_cmd(char *middle_cmd, int *p1, int *p2, char *path_env)
{
	char	*args[ARG_MAX];
	char	**cmd;
	int		arg_num;
	int		pid;

	arg_num = count_num_of_strings(middle_cmd, ' ');
	if (arg_num == 0)
		cust_write("Error(mid_cmd): Please provide a command.\n");
	cmd = ft_split(middle_cmd, ' ');
	args[arg_num] = NULL;
	while (0 <= --arg_num)
		args[arg_num] = cmd[arg_num];
	pid = fork();
	if (pid < 0)
		cust_perror("Error(mid_cmd)");
	if (pid == 0)
		middle_child(p1, p2, args, path_env);
	close(p1[0]);
	close(p1[1]);
	if (waitpid(-1, NULL, 0) == -1)
		cust_perror("Error(mid_cmd)");
	cust_free(cmd);
	free(cmd);
}

void	exec_last_cmd(char *last_cmd, char *output, int *p1, char *path_env)
{
	char	*args[ARG_MAX];
	char	**cmd;
	int		arg_num;
	int		pid;

	arg_num = count_num_of_strings(last_cmd, ' ');
	if (arg_num == 0)
		cust_write("Error(last_cmd): Please provide a command.\n");
	cmd = ft_split(last_cmd, ' ');
	args[arg_num] = NULL;
	while (0 <= --arg_num)
		args[arg_num] = cmd[arg_num];
	pid = fork();
	if (pid < 0)
		cust_perror("Error(last_cmd)");
	if (pid == 0)
		last_child(p1, args, output, path_env);
	close(p1[0]);
	close(p1[1]);
	if (waitpid(-1, NULL, 0) == -1)
		cust_perror("Error(last_cmd)");
	cust_free(cmd);
	free(cmd);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		p[ARG_MAX][2];
	char	*path_env;
	int		i;

	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", 9) == 0)
			heredoc(argv, argc, argv[2], envp);
		path_env = get_path_env(envp);
		if (pipe(p[0]) < 0)
			cust_perror("Error(main)");
		exec_first_cmd(argv, p[0], path_env);
		argc -= 2;
		i = 2;
		while (++i < argc)
		{
			if (pipe(p[i - 2]) < 0)
				cust_perror("Error(main)");
			exec_middle_cmd(argv[i], p[i - 3], p[i - 2], path_env);
		}
		exec_last_cmd(argv[argc], argv[argc + 1], p[i - 3], path_env);
	}
	else
		cust_write("Error(main): Give at least 4 args \n");
	return (0);
}
