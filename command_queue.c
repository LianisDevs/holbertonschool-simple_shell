#include "main.h"

argv_data_t *setup_command_queue(argv_data_t *argv)
{
	int queue_size = 50;

	argv->command_queue = (command_queue_t *)malloc(sizeof(command_queue_t));
	if (!argv->command_queue)
	{
		cleanup_argv(argv);
		exit(EXIT_FAILURE);
	}

	argv->command_queue->commands = (char **)malloc(queue_size * sizeof(char *));
	if (!argv->command_queue->commands)
	{
		clean_exit_general(argv);
		exit(EXIT_FAILURE);
	}

	argv->command_queue->position = 0;

	while (argv->command_queue->position < queue_size)
	{
		argv->command_queue->commands[argv->command_queue->position++] = NULL;
	}

	argv->command_queue->position = 0;

	return (argv);
}

command_queue_t *cleanup_command_queue(argv_data_t *argv)
{
	argv->command_queue->position = 0;

	while (argv->command_queue->commands[argv->command_queue->position] != NULL)
	{
		free(argv->command_queue->commands[argv->command_queue->position]);
		argv->command_queue->position++;
	}
	free(argv->command_queue->commands);
	free(argv->command_queue);
	argv->command_queue = NULL;

	return argv->command_queue;
}
