/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:57:25 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/06/03 14:47:55 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
		cust_perror("Error(first_cmd: fork)");
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
		cust_perror("Error(middle_cmd: fork)");
	if (cmd_p.pid == 0)
		middle_child(p1, p2, &cmd_p, pa);
	if (!((close(p1[0]) == 0) && (close(p1[1]) == 0)))
		cust_perror("Error(middle_cmd: close p1[0] or p1[1])");
	// if (waitpid(cmd_p.pid, &cmd_p.status, 0) == -1)
	// 	cust_perror("Error(second_cmd: waitpid)");
	// if (wait(NULL) == -1)
	// 	cust_perror("Error(second_cmd: wait)");
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
		cust_perror("Error(last_cmd: fork)");
	if (cmd_p.pid == 0)
		last_child(p1, &cmd_p, output, pa);
	if (!((close(p1[0]) == 0) && (close(p1[1]) == 0)))
		cust_perror("Error(last_cmd: close p1[0] or p1[1])");
	if (waitpid(cmd_p.pid, &cmd_p.status, 0) == -1)
		cust_perror("Error(last_cmd: waitpid)");
	if (wait(NULL) == -1)
		cust_perror("Error(last_cmd: wait)");
	cust_free(cmd_p.cmd_with_option);
	free(cmd_p.cmd_with_option);
	if (WIFEXITED(cmd_p.status))
		return (WEXITSTATUS(cmd_p.status));
	else
		return (WSTOPSIG(cmd_p.status));
}

int	main(int argc, char *argv[], char *envp[])
{
	t_param	pa;
	int		status;
	int		i;

	status = 0;
	pa.argv = argv;
	pa.envp = envp;
	if (!envp)
		exit(1);
	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", 9) == 0)
			return (heredoc(&pa, argc));
		if (access(argv[1], F_OK) != 0 || access(argv[1], R_OK) != 0)
			perror("Error(main: input file check)");
		pa.pathenv = get_value_of_pathenv(envp);
		if (pipe(pa.p[0]) < 0)
			cust_perror("Error(main: pipe p[0])");
		exec_first_cmd(pa.p[0], &pa);
		argc -= 2;
		i = 2;
		while (++i < argc)
		{
			if (pipe(pa.p[i - 2]) < 0)
				cust_perror("Error(main: pipe p[i -2]");
			exec_middle_cmd(argv[i], pa.p[i - 3], pa.p[i - 2], &pa);
		}
		status = exec_last_cmd(argv[i], argv[i + 1], pa.p[i - 3], &pa);
	}
	else
		cust_write("Error(main): Give 4 args (input, cmd1, cmd2, output)\n");
	return (status);
}
