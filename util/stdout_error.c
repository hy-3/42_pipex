#include "../src/pipex.h"

void	cust_perror(char *str)
{
	perror(str);
	exit(1);
}

void	cust_write(char *str)
{
	int	n;

	n = ft_strlen(str);
	write(1, str, n);
	exit(1);
}