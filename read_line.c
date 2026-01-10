#include "main.h"

/**
* read_line -
* @line: 
* Return: line or NULL on failure
*/

argv_data_t *read_line(argv_data_t *argv)
{
	char *buff = NULL;
	size_t length = 0;
	ssize_t line_read;
	
	argv->command_queue->commands[0] = NULL;

	/*checking if tty = interactive mode*/
	if (isatty(0) == 1)
	{
		printf("(: ");
		line_read = getline(&buff, &length, stdin);

		if (line_read != -1)
		{
			argv->command_queue->commands[argv->command_queue->position] = strdup(buff);
			free(buff);
			buff = NULL;
		}
		return (argv);
	}

	/*non interactive mode*/
	while ((line_read = getline(&buff, &length, stdin)) != -1)
	{
		if (strcmp(buff, "\n\0") != 0)
		{
			argv->command_queue->commands[argv->command_queue->position] = strdup(buff);
			argv->command_queue->position++;

			free(buff);
			buff = NULL;
		}
	}
	free(buff);
	buff = NULL;

	argv->command_queue->position = 0;
	return (argv);
}
