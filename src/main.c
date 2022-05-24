#include "pipex.h"

void	is_file_exist_and_readable(char *str)
{
	if (access(str, F_OK) != 0)
	{
		write(1, "Input file doesn't exist.\n", 26);
		exit(0);
	}
	if (access(str, R_OK) != 0)
	{
		write(1, "No read access to input file.\n", 29);
		exit(0);
	}
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
			perror("Error");
	}
	else
		perror("Error");
	return (NULL);
}

int	main(int argc, char *argv[])
{
	int		i;
	char	*args_first[ARG_MAX];
	char	**cmd_first;
	int		argnum_first;
	char	*path_first;

	int		p[2];

	char	*args_second[ARG_MAX];
	char	**cmd_second;
	int		argnum_second;
	char	*path_second;

	if (argc == 5)
	{
		//-- input file --
		is_file_exist_and_readable(argv[1]);

		//-- first cmd --
		argnum_first = count_num_of_strings(argv[2]);
		if (argnum_first == 0)
		{
			write(1, "Error: Please provide a command.\n", 33);
			exit(1);
		}
		cmd_first = cust_split(argv[2]);
		i = -1;
		while (++i < argnum_first)
			args_first[i] = cmd_first[i];
		args_first[argnum_first] = argv[1];
		args_first[argnum_first + 1] = NULL;
		path_first = is_cmd_exist_and_executable(args_first[0]);
		if (path_first == NULL)
			exit(1);
		if (pipe(p) < 0)
			exit(1);
		if (fork() == 0)
		{
			dup2(p[1], 1);
			execve(path_first, args_first, NULL);
		}
		else
			printf("else\n");
		// char inbuf[20];
		// read(p[0], inbuf, 20);
		//printf("read: %s\n", inbuf);

		//-- second cmd --
		argnum_second = count_num_of_strings(argv[3]);
		if (argnum_second == 0)
		{
			write(1, "Error: Please provide a command.\n", 33);
			exit(1);
		}
		cmd_second = cust_split(argv[2]);
		i = -1;
		while (++i < argnum_second)
			args_second[i] = cmd_second[i];
		args_second[argnum_first] = NULL;
		path_second = is_cmd_exist_and_executable(args_second[0]);
		if (path_second == NULL)
			exit(1);
		if (fork() == 0)
		{
			dup2(0, p[0]);
			execve(path_second, args_second, NULL);
		}
		else
			printf("else\n");

		//-- output file --
		// if (argv[4])
		// {
		// 	error handle when you couldn't create it or some other staffs.
		// }
	}
	else
		write(1, "Give 4 arguments(<Input File Name>, <Command 1>, <Command 2>, <Output File Name>)\n", 82);

	return (0);
}

//TODO: learn how to pass output to 2nd cmd & how to create output file with allowed funcs.
//ref: https://gist.github.com/iximiuz/65c7d2d128c374ef83d885dfef74bed7