#include "main.h"

/**
 * setup_argv - mallocs argv sets up fields inside struct
 * @argv: pointer to argv to setup
 * @command_queue: pointer to command_queue to free on failure
 * Return: pointer to argv
 */
argv_data_t *setup_argv(argv_data_t *argv, command_queue_t *command_queue)
{
	int arg_size = 50;

	argv = (argv_data_t *)malloc(sizeof(argv_data_t));

	if (!argv)
	{
		cleanup_command_queue(command_queue);
		exit(EXIT_FAILURE);
	}

	argv->args = (char **)malloc(arg_size * sizeof(char *));

	if (!argv->args)
	{
		free(argv);
		cleanup_command_queue(command_queue);
		exit(EXIT_FAILURE);
	}

	argv->position = 0;
	while (argv->position < arg_size)
		argv->args[argv->position++] = NULL;

	argv->path = NULL;
	argv->position = 0;

	return (argv);
}

/**
 * cleanup_argv - frees fields inside argv and argv
 * @argv: pointer to argv to free
 * Return: void
 */
void cleanup_argv(argv_data_t *argv)
{
	argv->position = 0;

	while (argv->args[argv->position] != NULL)
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

	free(argv);
	argv = NULL;
}

/**
 * reset_argv - calls cleanup_argv and frees line
 * @argv: pointer to argv to free
 * @command_queue: pointer to command_queue to increment position
 * @line: pointer to line to free
 * Return: void
 */
void reset_argv(argv_data_t *argv, command_queue_t *command_queue, char *line)
{
	cleanup_argv(argv);

	if (line)
	{
		free(line);
		line = NULL;
	}
	command_queue->position++;
}
