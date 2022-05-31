/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:57:38 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/05/31 16:48:32 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <limits.h>
# include <fcntl.h>
// for get_next_line
# include <sys/uio.h>
# include <stddef.h>

// src/child_bonus.c
void	first_child(int *p, char **args, char *input_file, char *path_env);
void	middle_child(int *p1, int *p2, char **args, char *path_env);
void	last_child(int *p, char **args, char *output_file, char *path_env);
void	exec_middle_cmd(char *middle_cmd, int *p1, int *p2, char *path_env);
void	exec_last_cmd(char *last_cmd, char *output, int *p1, char *path_env);
// src/heredoc/get_next_line_bonus.c
char	*get_next_line(int fd);
// src/heredoc/get_next_line_utils_bonus.c
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *str);
// src/heredoc/heredoc_bonus.c
void	heredoc(char *argv[], int argc, char *limiter, char *envp[]);
// util/check_bonus.c
void	is_file_exist_and_readable(char *str);
char	*get_path_env(char **envp);
char	*is_cmd_exist_and_executable(char *path_env, char *cmd);
// util/stderr_bonus.c
void	cust_perror(char *str);
void	cust_write(char *str);
// util/str_split_bonus.c
char	**ft_split(char const *s, char c);
int		count_num_of_strings(char const *s, char c);
void	cust_free(char **res);
// util/strnstr_bonus.c
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

#endif
