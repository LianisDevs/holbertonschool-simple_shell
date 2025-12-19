#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include "main.h"

int execute(argv_data_t *argv)
{
	/*pid_t my_pid;*/
	pid_t child_pid;
	int status;

	/*stat_t sb;*/

	/*make a fork and check it worked*/
	child_pid = fork();

	/*check if fork failed*/
	if (child_pid == -1)
	{
		perror("Error:");
		return(1);
	}

	/*my_pid = getpid();*/

	/*checking if we're on the fork*/
	if (child_pid == 0)
	{
		/*child does:*/
		status = execve(argv->args[0], argv->args, environ);

		if (status == -1)
			printf("Execve failed\n");

		printf("after\n");
		exit(EXIT_SUCCESS);
	}	
	else
	{
		/*parent does*/
		wait(&status);
	}
	return(1);
	/*use execve on the fork to run the program*/
	/*on main thread wait for it to finish*/
	/*continue*/
}
