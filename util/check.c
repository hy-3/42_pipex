#include "../src/pipex.h"

void	is_file_exist_and_readable(char *str)
{
	if (access(str, F_OK) != 0)
		cust_write("Error: Input file doesn't exist.\n");
	if (access(str, R_OK) != 0)
		cust_write("Error: No read access to input file.\n");
}

char	*is_cmd_exist_and_executable(char *cmd)
{
	char	*bin_cmd;
	char	*usr_cmd;

	bin_cmd = ft_strjoin(BIN_PATH, cmd);
	usr_cmd = ft_strjoin(USRBIN_PATH, cmd);
	if (access(bin_cmd, F_OK) == 0 || access(usr_cmd, F_OK) == 0)
	{
		if (access(bin_cmd, X_OK) == 0)
		{
			free(usr_cmd);
			return (bin_cmd);
		}
		else if (access(usr_cmd, X_OK) == 0)
		{
			free(bin_cmd);
			return (usr_cmd);
		}
		else
			cust_perror("Error");
	}
	else
		cust_perror("Error");
	return (NULL);
}
