/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:34:35 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/06/10 12:33:04 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	last_child_heredoc(int *p2, t_cmd_param *cmd_p, t_param *pa)
{
	int		fd;
	char	*cmd_path;

	if (close(p2[1]) == -1)
		cust_perror("Error(last_child_heredoc: close p1[1])", 1);
	if (dup2(p2[0], 0) == -1)
		cust_perror("Error(last_child_heredoc: dup2 p1[0])", 1);
	fd = open(pa->argv[5], O_CREAT | O_APPEND | O_WRONLY, 0777);
	if (fd == -1)
		cust_perror("Error(last_child_heredoc: open fd)", 1);
	if (dup2(fd, 1) == -1)
		cust_perror("Error(last_child_heredoc: dup2 fd)", 1);
	if (close(fd) == -1)
		cust_perror("Error(last_child: close fd)", 1);
	cmd_path = is_cmd_exist_and_executable(pa->pathenv, cmd_p->exec_args[0]);
	if (execve(cmd_path, cmd_p->exec_args, pa->envp) == -1)
		exit(127);
}

void	first_child_heredoc(int *p1, int *p2, t_cmd_param *cmd_p, t_param *pa)
{
	char	*cmd_path;

	if (close(p1[1]) == -1)
		cust_perror("Error(first_child_heredoc: close p1[1])", 1);
	if (close(p2[0]) == -1)
		cust_perror("Error(first_child_heredoc: close p2[0])", 1);
	if (dup2(p1[0], 0) == -1)
		cust_perror("Error(first_child_heredoc: dup2 p1[0])", 1);
	if (dup2(p2[1], 1) == -1)
		cust_perror("Error(first_child_heredoc: dup2 p2[1])", 1);
	cmd_path = is_cmd_exist_and_executable(pa->pathenv, cmd_p->exec_args[0]);
	if (execve(cmd_path, cmd_p->exec_args, pa->envp) == -1)
		exit(127);
}

int	exec_last_cmd_heredoc(t_param *pa, int *p2)
{
	t_cmd_param	cmd_p;

	cmd_p.n = count_num_of_strings(pa->argv[4], ' ');
	cmd_p.cmd_with_option = ft_split(pa->argv[4], ' ');
	if (cmd_p.cmd_with_option == NULL)
		cust_write("Error(last_cmd_heredoc): malloc failed\n", 1);
	cmd_p.exec_args[cmd_p.n] = NULL;
	while (0 <= --cmd_p.n)
		cmd_p.exec_args[cmd_p.n] = cmd_p.cmd_with_option[cmd_p.n];
	cmd_p.pid = fork();
	if (cmd_p.pid < 0)
		cust_perror("Error(last_cmd_heredoc: fork)", 1);
	if (cmd_p.pid == 0)
		last_child_heredoc(p2, &cmd_p, pa);
	if (!((close(p2[0]) == 0) && (close(p2[1]) == 0)))
		cust_perror("Error(second_cmd: close p1[0] or p1[1])", 1);
	if (waitpid(cmd_p.pid, &cmd_p.status, 0) == -1)
		cust_perror("Error(second_cmd: waitpid)", 1);
	if (wait(NULL) == -1)
		cust_perror("Error(second_cmd: wait)", 1);
	cust_free(cmd_p.cmd_with_option);
	free(cmd_p.cmd_with_option);
	return (wexitstatus(cmd_p.status));
}

void	exec_first_cmd_heredoc(t_param *pa, int *p1, int *p2)
{
	t_cmd_param	cmd_p;

	cmd_p.n = count_num_of_strings(pa->argv[3], ' ');
	cmd_p.cmd_with_option = ft_split(pa->argv[3], ' ');
	if (cmd_p.cmd_with_option == NULL)
		cust_write("Error(first_cmd_heredoc): malloc failed\n", 1);
	cmd_p.exec_args[cmd_p.n] = NULL;
	while (0 <= --cmd_p.n)
		cmd_p.exec_args[cmd_p.n] = cmd_p.cmd_with_option[cmd_p.n];
	cmd_p.pid = fork();
	if (cmd_p.pid < 0)
		cust_perror("Error(first_cmd_heredoc: fork)", 1);
	if (cmd_p.pid == 0)
		first_child_heredoc(p1, p2, &cmd_p, pa);
	if (!((close(p1[0]) == 0) && (close(p1[1]) == 0)))
		cust_perror("Error(second_cmd: close p1[0] or p1[1])", 1);
	cust_free(cmd_p.cmd_with_option);
	free(cmd_p.cmd_with_option);
}

int	heredoc(t_param *pa, int argc)
{
	char	*str;
	char	*limit_str;
	int		p1[2];
	int		p2[2];
	int		status;

	status = 0;
	if (argc != 6)
		cust_write("Error(here_doc): Args have to be 5.\n", 1);
	if (!((pipe(p1) == 0) && (pipe(p2) == 0)))
		cust_perror("Error(here_doc: pipe p1 or p2)", 1);
	limit_str = ft_strjoin(pa->argv[2], "\n");
	while (1)
	{
		str = get_next_line(0);
		if (ft_strncmp(str, limit_str, ft_strlen(pa->argv[2]) + 1) == 0)
			break ;
		write(p1[1], str, ft_strlen(str));
		free(str);
	}
	free(limit_str);
	pa->pathenv = get_value_of_pathenv(pa->envp);
	exec_first_cmd_heredoc(pa, p1, p2);
	status = exec_last_cmd_heredoc(pa, p2);
	return (status);
}
