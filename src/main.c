/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:57:25 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/06/09 15:07:54 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_first_cmd(int *p1, t_param *pa)
{
	t_cmd_param	cmd_p;

	cmd_p.n = count_num_of_strings(pa->argv[2], ' ');
	cmd_p.cmd_with_option = ft_split(pa->argv[2], ' ');
	cmd_p.exec_args[cmd_p.n] = NULL;
	while (0 <= --cmd_p.n)
		cmd_p.exec_args[cmd_p.n] = cmd_p.cmd_with_option[cmd_p.n];
	cmd_p.pid = fork();
	if (cmd_p.pid < 0)
		cust_perror("Error(first_cmd: fork)", 1);
	if (cmd_p.pid == 0)
		first_child(p1, &cmd_p, pa);
	cust_free(cmd_p.cmd_with_option);
	free(cmd_p.cmd_with_option);
}

void	exec_middle_cmd(char *middle_cmd, int *p1, int *p2, t_param *pa)
{
	t_cmd_param	cmd_p;

	cmd_p.n = count_num_of_strings(middle_cmd, ' ');
	cmd_p.cmd_with_option = ft_split(middle_cmd, ' ');
	cmd_p.exec_args[cmd_p.n] = NULL;
	while (0 <= --cmd_p.n)
		cmd_p.exec_args[cmd_p.n] = cmd_p.cmd_with_option[cmd_p.n];
	cmd_p.pid = fork();
	if (cmd_p.pid < 0)
		cust_perror("Error(middle_cmd: fork)", 1);
	if (cmd_p.pid == 0)
		middle_child(p1, p2, &cmd_p, pa);
	if (!((close(p1[0]) == 0) && (close(p1[1]) == 0)))
		cust_perror("Error(middle_cmd: close p1[0] or p1[1])", 1);
	cust_free(cmd_p.cmd_with_option);
	free(cmd_p.cmd_with_option);
}

int	exec_last_cmd(char *last_cmd, char *output, int *p1, t_param *pa)
{
	t_cmd_param	cmd_p;

	cmd_p.n = count_num_of_strings(last_cmd, ' ');
	cmd_p.cmd_with_option = ft_split(last_cmd, ' ');
	cmd_p.exec_args[cmd_p.n] = NULL;
	while (0 <= --cmd_p.n)
		cmd_p.exec_args[cmd_p.n] = cmd_p.cmd_with_option[cmd_p.n];
	cmd_p.pid = fork();
	if (cmd_p.pid < 0)
		cust_perror("Error(last_cmd: fork)", 1);
	if (cmd_p.pid == 0)
		last_child(p1, &cmd_p, output, pa);
	if (!((close(p1[0]) == 0) && (close(p1[1]) == 0)))
		cust_perror("Error(last_cmd: close p1[0] or p1[1])", 1);
	if (waitpid(cmd_p.pid, &cmd_p.status, 0) == -1)
		cust_perror("Error(last_cmd: waitpid)", 1);
	cust_free(cmd_p.cmd_with_option);
	free(cmd_p.cmd_with_option);
	return (wexitstatus(cmd_p.status));
}

void	cust_waitpid(int num_of_executed_cmd)
{
	while (num_of_executed_cmd-- > 0)
	{
		if (waitpid(-1, NULL, 0) == -1)
			cust_perror("Error(last_cmd: waitpid)", 1);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_param	pa;

	pa.result = 0;
	pa.argv = argv;
	pa.envp = envp;
	if (argc < 5)
		cust_write("Error(main): Give more than 4 args.\n", 1);
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		return (heredoc(&pa, argc));
	pa.pathenv = get_value_of_pathenv(envp);
	if (pipe(pa.p[0]) < 0)
		cust_perror("Error(main: pipe p[0])", 1);
	exec_first_cmd(pa.p[0], &pa);
	argc -= 2;
	pa.i = 2;
	while (++pa.i < argc)
	{
		if (pipe(pa.p[pa.i - 2]) < 0)
			cust_perror("Error(main: pipe p[i - 2]", 1);
		exec_middle_cmd(argv[pa.i], pa.p[pa.i - 3], pa.p[pa.i - 2], &pa);
	}
	pa.result = exec_last_cmd(argv[pa.i], argv[pa.i + 1], pa.p[pa.i - 3], &pa);
	cust_waitpid(pa.i - 2);
	return (pa.result);
}
