#include "main.h"

/**
* setup_command_queue - mallocs command_queue sets fields inside struct
* @command_queue: pointer to command_queue to set up
* Return: command_queue;
*/
command_queue_t *setup_command_queue(command_queue_t *command_queue)
{
	int queue_size = 50;

	command_queue = (command_queue_t *)malloc(sizeof(command_queue_t));

	if (!command_queue)
		exit(EXIT_FAILURE);

	command_queue->commands = (char **)malloc(queue_size * sizeof(char *));

	if (!command_queue->commands)
	{
		free(command_queue);
		exit(EXIT_FAILURE);
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
* cleanup_command_queue - frees fields inside command_queue and command_queue
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

/**
 * proccess_command_queue - processes the command queue from read line
 * @command_queue: pointer to command_queue
 * Return: pointer to command_queue
 */
command_queue_t *proccess_command_queue(command_queue_t *command_queue)
{
	argv_data_t *argv = NULL;
	char *line;
	int execute_result;

	while (command_queue->commands[command_queue->position] != NULL)
	{
		argv = setup_argv(argv, command_queue);
		line = strdup(command_queue->commands[command_queue->position]);

		/* when exit is entered- exit_success*/
		if (strcmp(line, "exit\n") == 0)
			exit_success(argv, command_queue, line);

		if (strcmp(line, "env\n") == 0)
		{
			print_env(argv, command_queue, line);
			continue;
		}

		/*split user's input*/
		split_line(argv, line);

		if (argv->args[0] == NULL)
		{
			reset_argv(argv, command_queue, line);
			continue;
		}

		if (valid_env(argv, command_queue, line) == 1)
			find_path(argv, command_queue, line);

		execute_result = execute(argv, command_queue, line);
		if (execute_result == 1)
			exit_general_error(argv, command_queue, line);

		/*free argv mallocs and line*/
		reset_argv(argv, command_queue, line);
	}
	return (command_queue);
}
