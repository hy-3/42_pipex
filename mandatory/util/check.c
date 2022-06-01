/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:57:51 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/06/01 16:41:17 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/pipex.h"

void	is_file_exist_and_readable(char *str)
{
	if (access(str, F_OK) != 0 || access(str, R_OK) != 0)
		perror("Error");
}

char	*get_value_of_pathenv(char **envp)
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

char	*omit_slash_and_take_last_word(char *cmd)
{
	int	i;
	int	position;

	i = 0;
	position = 0;
	while (cmd[i++] != '\0')
	{
		if (cmd[i] == '/')
			position = i + 1;
	}
	return (&cmd[position]);
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
		if (access(cmd, F_OK) == 0)
			return (cmd);
		// if (ft_strnstr(cmd, "/", ft_strlen(cmd)) != NULL)
		// 	cmd = omit_slash_and_take_last_word(cmd);
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
				perror("command isn't executable");
		}
		free(cmd_path);
	}
	perror("command not found");
	return (NULL);
}
