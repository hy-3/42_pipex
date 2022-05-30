/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:57:38 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/05/30 16:28:27 by hiyamamo         ###   ########.fr       */
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

# define BIN_PATH "/bin/"
# define USRBIN_PATH "/usr/bin/"

// child_bonus.c
void	first_child(int *p, char **args, char *input_file);
void	middle_child(int *p1, int *p2, char **args);
void	last_child(int *p, char **args, char *output_file);
// check_bonus.c
void	is_file_exist_and_readable(char *str);
char	*is_cmd_exist_and_executable(char *cmd);
// stderr_bonus.c
void	cust_perror(char *str);
void	cust_write(char *str);
// str_join_bonus.c
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
// str_split_bonus.c
char	**ft_split(char const *s, char c);
int		count_num_of_strings(char const *s, char c);

#endif
