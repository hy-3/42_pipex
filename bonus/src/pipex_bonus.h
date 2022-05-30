/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:57:38 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/05/30 18:41:09 by hiyamamo         ###   ########.fr       */
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

// src/child_bonus.c
void	first_child(int *p, char **args, char *input_file, char *path_env);
void	middle_child(int *p1, int *p2, char **args, char *path_env);
void	last_child(int *p, char **args, char *output_file, char *path_env);
// util/check_bonus.c
void	is_file_exist_and_readable(char *str);
char	*get_path_env(char **envp);
char	*is_cmd_exist_and_executable(char *path_env, char *cmd);
// util/stderr_bonus.c
void	cust_perror(char *str);
void	cust_write(char *str);
// util/str_join_bonus.c
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
// util/str_split_bonus.c
char	**ft_split(char const *s, char c);
int		count_num_of_strings(char const *s, char c);
void	cust_free(char **res);
// util/strnstr_bonus.c
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

#endif
