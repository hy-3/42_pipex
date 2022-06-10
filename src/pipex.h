/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:57:38 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/06/10 12:31:42 by hiyamamo         ###   ########.fr       */
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
// for get_next_line
# include <sys/uio.h>
# include <stddef.h>

typedef struct s_param
{
	char	**argv;
	char	**envp;
	int		p[ARG_MAX][2];
	char	*pathenv;
	int		result;
	int		i;
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
// src/child.c
void	first_child(int *p1, t_cmd_param *cmd_p, t_param *pa);
void	middle_child(int *p1, int *p2, t_cmd_param *cmd_p, t_param *pa);
void	last_child(int *p1, t_cmd_param *cmd_p, char *output, t_param *pa);
// src/heredoc/util/get_next_line.c
char	*get_next_line(int fd);
// src/heredoc/util/get_next_line_utils.c
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
// src/heredoc/heredoc.c
int		heredoc(t_param *pa, int argc);
// src/status.c
int		wexitstatus(int status);
// src/stderr.c
void	cust_perror(char *str, int status);
void	cust_write(char *str, int status);
// util/str_split.c
char	**ft_split(char const *s, char c);
int		count_num_of_strings(char const *s, char c);
void	cust_free(char **res);
// util/str_search.c
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
