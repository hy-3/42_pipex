#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h> //TODO: Delete

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <limits.h>

# define BIN_PATH "/bin/"
# define USRBIN_PATH "/usr/bin/"

char	**cust_split(char const *s);
int		count_num_of_strings(char const *s);
char	*ft_strjoin(char const *s1, char const *s2);

#endif