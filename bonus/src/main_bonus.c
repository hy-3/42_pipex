/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:57:25 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/05/30 16:50:49 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec_first_cmd(char *argv[], int *p1)
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
		first_child(p1, args, argv[1]);
	if (waitpid(-1, NULL, 0) == -1)
		cust_perror("Error");
}

void	exec_middle_cmd(char *middle_cmd, int *p1, int *p2)
{
	char	*args[ARG_MAX];
	char	**cmd;
	int		arg_num;
	int		pid;

	arg_num = count_num_of_strings(middle_cmd, ' ');
	if (arg_num == 0)
		cust_write("Error: Please provide a command.\n");
	cmd = ft_split(middle_cmd, ' ');
	args[arg_num] = NULL;
	while (0 <= --arg_num)
		args[arg_num] = cmd[arg_num];
	pid = fork();
	if (pid < 0)
		cust_perror("Error");
	if (pid == 0)
		middle_child(p1, p2, args);
	close(p1[0]);
	close(p1[1]);
	if (waitpid(-1, NULL, 0) == -1)
		cust_perror("Error");
}

void	exec_last_cmd(char *last_cmd, char *output_file, int *p1)
{
	char	*args[ARG_MAX];
	char	**cmd;
	int		arg_num;
	int		pid;

	arg_num = count_num_of_strings(last_cmd, ' ');
	if (arg_num == 0)
		cust_write("Error: Please provide a command.\n");
	cmd = ft_split(last_cmd, ' ');
	args[arg_num] = NULL;
	while (0 <= --arg_num)
		args[arg_num] = cmd[arg_num];
	pid = fork();
	if (pid < 0)
		cust_perror("Error");
	if (pid == 0)
		last_child(p1, args, output_file);
	close(p1[0]);
	close(p1[1]);
	if (waitpid(-1, NULL, 0) == -1)
		cust_perror("Error");
}

int	main(int argc, char *argv[])
{
	int	p[ARG_MAX][2];
	int	i;

	if (argc >= 5)
	{
		is_file_exist_and_readable(argv[1]);
		if (pipe(p[0]) < 0)
			cust_perror("Error");
		exec_first_cmd(argv, p[0]);
		argc -= 2;
		i = 3;
		while (i < argc)
		{
			if (pipe(p[i - 2]) < 0)
				cust_perror("Error");
			exec_middle_cmd(argv[i], p[i - 3], p[i - 2]);
			i++;
		}
		exec_last_cmd(argv[argc], argv[argc + 1], p[i - 3]);
	}
	else
		cust_write("Error: Give at least 4 args \n");
	return (0);
}

//TODO: fix: take cmd path from environment
//TODO: implement here_doc