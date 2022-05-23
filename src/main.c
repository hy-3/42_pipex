#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

#include <stdio.h>
int	main(int argc, char *argv[])
{
	// -- Fork --
	// You have to fork and run execve as a child process.

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
	const char *path = "/bin/cat";
	char *const args[] = {"/bin/cat", "a.txt"};
	execve(path, args, NULL);

/*
	if (argc == 5)
	{
		if (access(argv[1], xxx) != 0)
		{
			write(1, "Input file permission failed.\n");
			// use perror or strerror and shows error message based on errono.
		}
		if (argv[2] && argv[3])
		{
			// check if it is accessible & executable.
		}
		if (argv[4])
		{
			// error handle when you couldn't create it or some other staffs.
		}

	}
	else
		write(1, "Give 4 arguments(<Input File Name>, <Command 1>, <Command 2>, <Output File Name>)\n", 82);
*/
	return (0);
}

// 