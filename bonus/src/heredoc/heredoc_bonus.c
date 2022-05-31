/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:34:35 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/05/31 18:06:21 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	last_child_heredoc(int *p1, char **args, char *output, char *path_env)
{
	int		fd;
	char	*cmd_path;

	close(p1[1]);
	if (dup2(p1[0], 0) == -1)
		cust_perror("Error(last_child_heredoc)");
	fd = open(output, O_CREAT | O_APPEND | O_WRONLY, 0777);
	if (dup2(fd, 1) == -1)
		cust_perror("Error(last_child_heredoc)");
	close(fd);
	cmd_path = is_cmd_exist_and_executable(path_env, args[0]);
	execve(cmd_path, args, NULL);
	free(cmd_path);
}

void	exec_last_cmd_heredoc(char *last_cmd, char *output, \
									int *p1, char *path_env)
{
	char	*args[ARG_MAX];
	char	**cmd;
	int		arg_num;
	int		pid;

	arg_num = count_num_of_strings(last_cmd, ' ');
	if (arg_num == 0)
		cust_write("Error(last_cmd_heredoc): Please provide a command.\n");
	cmd = ft_split(last_cmd, ' ');
	args[arg_num] = NULL;
	while (0 <= --arg_num)
		args[arg_num] = cmd[arg_num];
	pid = fork();
	if (pid < 0)
		cust_perror("Error(last_cmd_heredoc)");
	if (pid == 0)
		last_child_heredoc(p1, args, output, path_env);
	close(p1[0]);
	close(p1[1]);
	if (waitpid(-1, NULL, 0) == -1)
		cust_perror("Error(last_cmd_heredoc)");
	cust_free(cmd);
	free(cmd);
}

void	heredoc(char *argv[], int argc, char *limiter, char *envp[])
{
	char	*str;
	int		p1[2];
	int		p2[2];
	char	*path_env;

	if (argc != 6)
		cust_write("Error(here_doc): Args have to be 5.\n");
	if (pipe(p1) < 0)
		cust_perror("Error(here_doc)");
	if (pipe(p2) < 0)
		cust_perror("Error(here_doc)");
	while (1)
	{
		str = get_next_line(0);
		if (ft_strncmp(str, ft_strjoin(limiter, "\n"), \
				ft_strlen(limiter) + 1) == 0)
			break ;
		write(p1[1], str, ft_strlen(str));
	}
	path_env = get_path_env(envp);
	exec_middle_cmd(argv[3], p1, p2, path_env);
	exec_last_cmd_heredoc(argv[4], argv[5], p2, path_env);
	exit (0);
}
