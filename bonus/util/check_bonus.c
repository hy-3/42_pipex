/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:57:51 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/05/31 16:45:05 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/pipex_bonus.h"

void	is_file_exist_and_readable(char *str)
{
	if (access(str, F_OK) != 0)
		cust_write("Error(file check): Input file doesn't exist.\n");
	if (access(str, R_OK) != 0)
		cust_write("Error(file check): No read access to input file.\n");
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
		cust_write("Error(env): no PATH env in envirnment variables.\n");
	res += 5;
	return (res);
}

char	*create_cmd_path(char *each_path, char *cmd)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(each_path, "/");
	res = ft_strjoin(tmp, cmd);
	free(tmp);
	return (res);
}

char	*is_cmd_exist_and_executable(char *path_env, char *cmd)
{
	int		arg_num;
	char	**each_path;
	char	*cmd_path;

	arg_num = count_num_of_strings(path_env, ':');
	each_path = ft_split(path_env, ':');
	while (0 <= --arg_num)
	{
		cmd_path = create_cmd_path(each_path[arg_num], cmd);
		if (access(cmd_path, F_OK) == 0)
		{
			if (access(cmd_path, X_OK) == 0)
			{
				cust_free(each_path);
				free(each_path);
				return (cmd_path);
			}
			else
				cust_perror("Error");
		}
		free(cmd_path);
	}
	cust_perror("Error");
	return (NULL);
}
