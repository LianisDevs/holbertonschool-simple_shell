#include "main.h"

/**
* read_line -
* @line: 
* Return: line or NULL on failure
*/

command_queue_t *read_line(command_queue_t *command_queue)
{
	char *buff = NULL;
	size_t length = 0;
	ssize_t line_read;
	
	command_queue->commands[0] = NULL;

	/*checking if tty = interactive mode -------->*/
	if (isatty(0) == 1)
	{
		printf("(: ");
		line_read = getline(&buff, &length, stdin);

		if (line_read != -1)
		{
			command_queue->commands[command_queue->position] = strdup(buff);
			free(buff);
			buff = NULL;
		}
		return (command_queue);
	}


	/* non interactive mode ------>*/
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
