/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:57:51 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/05/30 16:48:56 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/pipex.h"

void	is_file_exist_and_readable(char *str)
{
	if (access(str, F_OK) != 0)
		cust_write("Error: Input file doesn't exist.\n");
	if (access(str, R_OK) != 0)
		cust_write("Error: No read access to input file.\n");
}

char	*get_path_env(char **envp)
{
	char	*res;
	int		i;

	res = NULL;
	i = 0;
	while (envp[i])
	{
		res = ft_strnstr(envp[i++], "PATH=", 5);
		if (res != NULL)
			break ;
	}
	if (res == NULL)
		cust_write("Error: PATH env can't be found from envirnment variables");
	res += 5;
	return (res);
}

char	*is_cmd_exist_and_executable(char *path_env, char *cmd)
{
	int		arg_num;
	char	**each_path;
	char	*cmd_path;

	arg_num = count_num_of_strings(path_env, ':');
	if (arg_num == 0)
		cust_write("Error: nothing set on PATH env.\n");
	each_path = ft_split(path_env, ':');
	while (0 <= --arg_num)
	{
		cmd_path = ft_strjoin(ft_strjoin(each_path[arg_num], "/"), cmd);
		if (access(cmd_path, F_OK) == 0)
		{
			if (access(cmd_path, X_OK) == 0)
				return (cmd_path);
			else
				cust_perror("Error");
		}
		free(cmd_path);
	}
	cust_perror("Error");
	return (NULL);
}
