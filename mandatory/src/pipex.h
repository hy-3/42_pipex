/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:57:38 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/06/01 18:45:03 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <limits.h>
# include <fcntl.h>

typedef struct s_param
{
	char	**argv;
	char	**envp;
	int		p[2];
	char	*pathenv;

}	t_param;

typedef struct s_cmd_param
{
	char	*exec_args[ARG_MAX];
	char	**cmd_with_option;
	int		n;
	int		pid;
	int		status;
}	t_cmd_param;

// src/check_cmd.c
char	*get_value_of_pathenv(char **envp);
char	*is_cmd_exist_and_executable(char *path_env, char *cmd);
// src/stderr.c
void	cust_perror(char *str);
void	cust_write(char *str);
// util/str_join.c
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
// util/str_split.c
char	**ft_split(char const *s, char c);
int		count_num_of_strings(char const *s, char c);
void	cust_free(char **res);
// util/strnstr.c
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

#endif
