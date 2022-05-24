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
	// -- Execve --
	/*
	path to linux commands execution files.
		/bin
		/usr/bin
	*/
	// const char *path = "/bin/ls";
	// char *const args[] = {"/bin/ls", "-lh"};
	// const char *path = "/bin/date";
	// char *const args[] = {"/bin/date", "-u"};
	// const char *path = "/bin/cat";
	// char *const args[] = {"/bin/cat", "a.txt"};
	// execve(path, args, NULL);

	char	*i_file;
	int		pid;

	int		i;
	char	*args_first[ARG_MAX];
	char	**cmd_first;
	int		argnum_first;
	char	*path_first;

	char	*args_second[ARG_MAX];
	char	**cmd_second;
	int		argnum_second;

	if (argc == 5)
	{
		is_file_exist_and_readable(argv[1]);

		argnum_first = count_num_of_strings(argv[2]);
		if (argnum_first == 0)
		{
			write(1, "Please provide a command.\n", 26);
			exit(0);
		}
		cmd_first = cust_split(argv[2]);
		i = -1;
		while (++i < argnum_first)
			args_first[i] = cmd_first[i];
		args_first[argnum_first] = argv[1];
		args_first[argnum_first + 1] = NULL;
		path_first = is_cmd_exist_and_executable(args_first[0]);
		if (path_first == NULL)
			exit(0);

		// if (fork() == 0)
		// {
		// 	printf("ch\n");
		// }
		// else
		// 	printf("else\n");

		execve(path_first, args_first, NULL); //won't print to srdin if run in child process.



		// if (argv[4])
		// {
		// 	error handle when you couldn't create it or some other staffs.
		// }
	}
	else
		write(1, "Give 4 arguments(<Input File Name>, <Command 1>, <Command 2>, <Output File Name>)\n", 82);

	return (0);
}


//TODO: use perror or strerror and shows error message based on errono?