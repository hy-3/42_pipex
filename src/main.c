#include "pipex.h"

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

void	exec_first_cmd(char *argv[], int *p, int pid)
{
	char	*args[ARG_MAX];
	char	**cmd;
	int		arg_num;
	char	*path;

	arg_num = count_num_of_strings(argv[2]);
	if (arg_num == 0)
		cust_write("Error: Please provide a command.\n");
	cmd = cust_split(argv[2]);
	args[arg_num] = argv[1];
	args[arg_num + 1] = NULL;
	while (0 <= --arg_num)
		args[arg_num] = cmd[arg_num];
	path = is_cmd_exist_and_executable(args[0]);
	pid = fork();
	if (pid < 0)
		cust_perror("Error");
	if (pid == 0)
	{
		close(p[0]);
		dup2(p[1], 1);
		execve(path, args, NULL);
	}
}

void	exec_second_cmd(char *argv[], int *p, int pid)
{
	char	*args[ARG_MAX];
	char	**cmd;
	int		arg_num;
	char	*path;

	arg_num = count_num_of_strings(argv[3]);
	if (arg_num == 0)
		cust_write("Error: Please provide a command.\n");
	cmd = cust_split(argv[3]);
	args[arg_num] = NULL;
	while (0 <= --arg_num)
		args[arg_num] = cmd[arg_num];
	path = is_cmd_exist_and_executable(args[0]);
	pid = fork();
	if (pid < 0)
		cust_perror("Error");
	if (pid == 0)
	{
		close(p[1]);
		dup2(p[0], 0);
		execve(path, args, NULL);
	}
}

int	main(int argc, char *argv[])
{
	int	p[2];
	int	pid;

	if (argc == 5)
	{
		is_file_exist_and_readable(argv[1]);
		if (pipe(p) < 0)
			cust_perror("Error");
		exec_first_cmd(argv, p, pid);
		if (waitpid(-1, NULL, 0) == -1)
			cust_perror("Error");
		exec_second_cmd(argv, p, pid);
		close(p[0]);
		close(p[1]);
		if (waitpid(-1, NULL, 0) == -1)
			cust_perror("Error");

		//-- output file --
		// if (argv[4])
		// {
		// 	error handle when you couldn't create it or some other staffs.
		// }
	}
	else
		cust_write("Error: Give 4 args(input file, cmd1, cmd2, output file)");
	return (0);
}
