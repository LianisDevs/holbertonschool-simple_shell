#include "main.h"

/**
 * main - main file for simple shell
 *		  contains the forever while loop to run the shell
 * Return: 0 on success 1 on failure
 */

int main(void)
{
	command_queue_t *command_queue = NULL;

	while (true)
	{
		command_queue = setup_command_queue(command_queue);
		if (command_queue == NULL)
			exit (EXIT_FAILURE);

		/*get the user's input*/
		command_queue = read_line(command_queue);

		if (!command_queue->commands[0])
		{
			cleanup_command_queue(command_queue);
			command_queue = NULL;
			continue;
		}
		proccess_command_queue(command_queue);

		cleanup_command_queue(command_queue);
		command_queue = NULL;

		if (isatty(0) == 0)
			return (0);
	}
	return (0);
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
	int find_path_result, execute_result;

	while (command_queue->commands[command_queue->position] != NULL)
	{
		/*setup the argv array*/
		argv = setup_argv(argv);
		if (argv == NULL)
		{
			cleanup_command_queue(command_queue);
			exit (EXIT_FAILURE);
		}
		line = strdup(command_queue->commands[command_queue->position]);

		/* TODO... this will be exit condition later*/
		if (strcmp(line, "exit\n") == 0)
			exit_success(argv, command_queue, line);

		/*split user's input*/
		split_line(argv, line);

		if (argv->args[0] == NULL)
		{
			reset_argv(argv, line);
			command_queue->position++;
			continue;
		}

		if (valid_env(argv, command_queue, line) == 1)
		{
			find_path_result = find_path(argv);

			if (find_path_result == 1)
				exit_command_not_found(argv, command_queue, line);
		}

		execute_result = execute(argv, command_queue, line);
		if (execute_result == 1)
			exit_general_error(argv, command_queue, line);

		/*free argv mallocs and line*/
		reset_argv(argv, line);

		command_queue->position++;
	}
	return (command_queue);
}
