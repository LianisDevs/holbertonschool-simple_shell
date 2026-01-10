#include "main.h"

/**
 * execute- creates fork to execute the valid command
 * @argv: pointer to argv to free
 * Return: 0 on success 1 on failure
 */

int execute(argv_data_t *argv)
{
	pid_t child_pid;
	int status;
	int execve_result = 0;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error:");
		return (1);
	}
	if (child_pid == 0)
	{
		if (argv->args[0] != NULL)
			execve_result = execve(argv->args[0], argv->args, environ);

		if (execve_result == -1)
			return (1);
	}
	else
		wait(&status);

	return (0);
}
