#include "main.h"

/**
 * main - main file for simple shell
 *		  contains the forever while loop to run the shell
 * Return: 0 on success 1 on error
 */

int main(void)
{
	command_queue_t *command_queue = NULL;
	char *line;
	argv_data_t *argv;
	int execute_result, find_path_result;
	struct stat statbuff;

	while (true)
	{
		command_queue = setup_command_queue(command_queue);
		if (command_queue == NULL)
			return (1);

		/*get the user's input*/
		command_queue = read_line(command_queue);
		
		if (!command_queue->commands[0])
		{
			cleanup_command_queue(command_queue);
			return (1);
		}

		while (command_queue->commands[command_queue->position] != NULL)
		{
			line = strdup(command_queue->commands[command_queue->position]);

			/* TODO... this will be exit condition later*/
			if (strcmp(line, "exit\n") == 0)
			{
				free(line);
				cleanup_command_queue(command_queue);
				return (0);
			}

			/*setup the argv array*/
			argv = setup_argv(argv);

			if (argv == NULL)
			{
				free(line);
				cleanup_command_queue(command_queue);
				return (1);
			}

			/*split user's input*/
			split_line(line, argv);
			
			if (valid_env(argv, command_queue, line) == 1 && stat(argv->args[0], &statbuff) == -1)
			{
				find_path_result = find_path(argv);
			
				if (find_path_result == 1)
				{
					fprintf(stderr, "./hsh: 1: %s: not found\n", argv->args[0]);
					cleanup_argv(argv);
					cleanup_command_queue(command_queue);
					free(line);
					exit (127);
				}
			}

			execute_result = execute(argv);

			if (execute_result == 1) 
			{
				cleanup_argv(argv);
				cleanup_command_queue(command_queue);
				free(line);
				return (1);
			}

			/*free all mallocs*/
			cleanup_argv(argv);
			free(line);
			line = NULL;
			command_queue->position++;
		}
		cleanup_command_queue(command_queue);
		command_queue = NULL;

		if (isatty(0) == 0)
			return (0);

	}
	return (0);
}
