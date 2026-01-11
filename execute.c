#include "main.h"

/**
 * execute- creates fork to execute the valid command
 * @argv: pointer to argv
 * @command_queue: pointer to command_queue to free if failure
 * @line: pointer to line to free if failure
 * Return: 0 on success 1 on failure
 */

int execute(argv_data_t *argv, command_queue_t *command_queue, char *line)
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
	} else
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			status = WEXITSTATUS(status);

			if (status == 2)
				exit_command_failed(argv, command_queue, line, status);
		}
	}
	return (0);
}
