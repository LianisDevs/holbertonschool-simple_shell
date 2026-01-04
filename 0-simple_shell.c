#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "main.h"

int main (void) {
	char *line = NULL;
	argv_data_t *argv;
	pid_t child_pid;
	int execve_result, status;

	while (true)
	{
		line = read_line(line);

		if (!line)
			return (0);

		if (strcmp(line, "exit\n") == 0)
		{
			free(line);
			return (0);
		};

		argv = setup_argv(argv);

		if (argv == NULL)
			return(1);

		split_line(line, argv);

		child_pid = fork();

		if (child_pid == -1)
		{
			perror("Error:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve_result = execve(argv->args[0], argv->args, environ);

			if (execve_result == -1)
				return (1);
		}
		else 
			wait(&status);
		
		cleanup_argv(argv);
		free(line);
		line = NULL;
	}
	return (0);
}
