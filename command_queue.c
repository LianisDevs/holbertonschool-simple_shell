#include "main.h"

command_queue_t *setup_command_queue(command_queue_t *command_queue)
{
	int queue_size = 50;

	command_queue = (command_queue_t *)malloc(sizeof(command_queue_t));

	if (!command_queue)
		return (command_queue);

	command_queue->commands = (char **)malloc(queue_size * sizeof(char *));

	if (!command_queue->commands)
	{
		free(command_queue);
		command_queue = NULL;
		return (command_queue);
	}

	command_queue->position = 0;

	while (command_queue->position < queue_size)
	{
		command_queue->commands[command_queue->position++] = NULL;
	}

	command_queue->position = 0;
	return (command_queue);
}

void cleanup_command_queue(command_queue_t *command_queue)
{
	command_queue->position = 0;

	while (command_queue->commands[command_queue->position] != NULL)
	{
		free(command_queue->commands[command_queue->position]);
		command_queue->position++;
	}
	free(command_queue->commands);

	free(command_queue);
	command_queue = NULL;

	return;
}
