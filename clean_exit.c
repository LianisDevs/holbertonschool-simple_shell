#include "main.h"

/**
 * exit_success - frees all malloced elements and EXIT_SUCCESS
 * @argv: pointer to argv to free
 * @command_queue: pointer to command_queue to free
 * @line: pointer to line to free
 * Return: void
 */
void exit_success(argv_data_t *argv,
				  command_queue_t *command_queue, char *line)
{
	if (line)
		free(line);

	cleanup_command_queue(command_queue);

	if (argv)
		cleanup_argv(argv);

	exit(EXIT_SUCCESS);
}

/**
 * exit_general_error - frees all malloced elements and EXIT_FAILURE
 * @argv: pointer to argv to free
 * @command_queue: pointer to command_queue to free
 * @line: pointer to line to free
 * Return: void
 */
void exit_general_error(argv_data_t *argv,
						command_queue_t *command_queue, char *line)
{
	free(line);
	cleanup_command_queue(command_queue);
	cleanup_argv(argv);
	exit(EXIT_FAILURE);
}

/**
 * exit_command_not_found - frees all malloced elements and EXITS 127
 * @argv: pointer to argv to free
 * @command_queue: pointer to command_queue to free
 * @line: pointer to line to free
 * Return: void
 */
void exit_command_not_found(argv_data_t *argv,
							command_queue_t *command_queue, char *line)
{
	fprintf(stderr, "./hsh: 1: %s: not found\n", argv->args[0]);
	free(line);
	cleanup_command_queue(command_queue);
	cleanup_argv(argv);
	exit(127);
}

void exit_command_failed(argv_data_t *argv,
						 command_queue_t *command_queue, char *line, int status)
{
	free(line);
	cleanup_command_queue(command_queue);
	cleanup_argv(argv);
	exit(status);
}
