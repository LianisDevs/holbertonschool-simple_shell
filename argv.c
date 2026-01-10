#include "main.h"

void *setup_argv_args(argv_data_t *argv);

argv_data_t *setup_argv(argv_data_t *argv)
{
	argv = (argv_data_t *)malloc(sizeof(argv_data_t));

	if(!argv)
		exit(EXIT_FAILURE);

	argv->args = (char **)malloc(50 * sizeof(char *));

	if(!argv->args)
	{
		free(argv);
		exit(EXIT_FAILURE);
	}

	setup_argv_args(argv);
	argv->path = NULL;
	argv->line = NULL;

	setup_command_queue(argv);

	return (argv);
}

argv_data_t *cleanup_argv(argv_data_t *argv)
{
	argv->position = 0;

	while (argv->args != NULL && argv->args[argv->position] != NULL)
	{
		free(argv->args[argv->position]);
		argv->position++;
	}

	free(argv->args);
	argv->args = NULL;

	if (argv->path)
	{
		free(argv->path);
		argv->path = NULL;
	}

	argv->command_queue = cleanup_command_queue(argv);
	argv->command_queue = NULL;
	free(argv->line);
	free(argv->path);
	free(argv);
	argv = NULL;

	return argv;
}

argv_data_t *reset_argv(argv_data_t *argv)
{
	argv->position = 0;

	while (argv->args[argv->position] != NULL)
	{
		free(argv->args[argv->position]);
		argv->args[argv->position] = NULL;
		argv->position++;
	}
	free(argv->line);
	free(argv->args);
	argv->args = NULL;
	argv->line = NULL;

	argv->position = 0;

	return argv;
}

void argv_printer(argv_data_t *argv)
{
	int queue_size = 50;
	if (argv == NULL) {
		printf("No arg");
		return;
	}
	if (argv != NULL) {
		argv->position = 0;
		if (argv->args != NULL) {
			while (argv->position < queue_size) {
				printf("args %d", argv->position);
				if (argv->args[argv->position] != NULL)
					printf(" is %s\n", argv->args[argv->position]);
				argv->position++;
			}
		}
		argv->position = 0;
	}
	if (argv != NULL) {
		if(argv->command_queue != NULL) {
			argv->command_queue->position = 0;
			while (argv->command_queue->position < queue_size && argv->command_queue->commands != NULL) {
				printf("command %d", argv->command_queue->position);
				if (argv->command_queue->commands[argv->command_queue->position] != NULL)
					printf(" is %s\n", argv->command_queue->commands[argv->command_queue->position]);
				argv->command_queue->position++;
			}

		}
		argv->command_queue->position = 0;
	}
}

void *setup_argv_args(argv_data_t *argv)
{
	int queue_size = 50;

	argv->position = 0;

	while (argv->position < queue_size)
	{
		argv->args[argv->position++] = NULL;
	}

	argv->position = 0;

	return (argv);
}
