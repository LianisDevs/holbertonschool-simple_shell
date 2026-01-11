#include "main.h"


/**
 * print_env - built in version of env
 * @argv: pointer to argv to reset
 * @command_queue: pointer to command_queue to increment position
 * @line: pointer to line to free
 * Return: void
 */
void print_env(argv_data_t *argv, command_queue_t *command_queue, char *line)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
	reset_argv(argv, command_queue, line);
}
