#include "main.h"

/**
* setup_command_queue - mallocs command_queue sets up elements inside struct
* @command_queue: pointer to command_queue to set up
* Return: command_queue;
*/
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

/**
* cleanup_command_queue - frees elements inside command_queue and command_queue
* @command_queue: pointer to command_queue to free
* Return: void;
*/
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
}
