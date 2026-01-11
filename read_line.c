#include "main.h"

/**
* read_line - reads input from user and adds this to command_queue
* @command_queue: pointer to command_queue
* Return: command_queue
*/
command_queue_t *read_line(command_queue_t *command_queue)
{
	char *buff = NULL;
	size_t length = 0;
	ssize_t line_read;

	/*checking if tty = interactive mode*/
	if (isatty(0) == 1)
	{
		printf("(: ");
		line_read = getline(&buff, &length, stdin);

		if (line_read != -1)
		{
			if (strcmp(buff, "\n\0") != 0)
			{
				command_queue->commands[command_queue->position] = strdup(buff);
			} else
			{
				command_queue->commands[command_queue->position] = NULL;
			}
			free(buff);
			buff = NULL;
		}
		return (command_queue);
	}

	/* non interactive mode*/
	return (read_line_non_interact(command_queue));
}

/**
* read_line_non_interact - reads input from user in non interactive mode
*						   and adds this to command_queue
*
* @command_queue: pointer to command_queue
* Return: command_queue
*/
command_queue_t *read_line_non_interact(command_queue_t *command_queue)
{
	char *buff = NULL;
	size_t length = 0;
	ssize_t line_read;

	while ((line_read = getline(&buff, &length, stdin)) != -1)
	{
		if (strcmp(buff, "\n\0") != 0)
		{
			command_queue->commands[command_queue->position] = strdup(buff);
			command_queue->position++;

			free(buff);
			buff = NULL;
		}
	}
	free(buff);
	buff = NULL;

	command_queue->position = 0;
	return (command_queue);
}
