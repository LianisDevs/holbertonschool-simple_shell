#include "main.h"

/**
 * main - main file for simple shell
 *		  contains the forever while loop to run the shell
 * Return: 0 on success 1 on error
 */

int main(void)
{
	argv_data_t *argv = NULL;
	int execute_result, find_path_result;

	while (true)
	{
		/*setup argv*/
		argv = setup_argv(argv);

		/*get user's input*/
		argv = read_line(argv);
		
		/*check read_line failure*/
		if (!argv->command_queue->commands[0])
			clean_exit_general(argv);

		while (argv->command_queue->commands[argv->command_queue->position] != NULL)
		{
			argv->line = strdup(argv->command_queue->commands[argv->command_queue->position]);

			/* TODO... this will be exit condition later*/
			if (strcmp(argv->line, "exit\n") == 0)
				clean_exit_success(argv);

			/*split user's input*/
			split_line(argv);
			
			if ((find_path_result = find_path(argv)))
			{
				valid_env(argv);

				if (find_path_result == 1)
					clean_exit_command_not_found(argv);
			}

			execute_result = execute(argv);

			if (execute_result == 1) 
				clean_exit_general(argv);

			/*free all mallocs*/
			argv = reset_argv(argv);
			argv->command_queue->position++;
		}

		argv = cleanup_argv(argv);

		if (isatty(0) == 0)
			exit(EXIT_SUCCESS);
	}

	exit(EXIT_SUCCESS);
}
