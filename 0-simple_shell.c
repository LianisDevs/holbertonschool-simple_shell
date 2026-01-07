#include "main.h"

/**
 * main - main file for simple shell
 *		  contains the forever while loop to run the shell
 * Return: 0 on success 1 on error
 */

int main(void)
{
	char *line = NULL;
	argv_data_t *argv;
	int execute_result, find_path_result;

	while (true)
	{
		/*get the user's input*/
		line = read_line(line);

		if (!line)
			return (0);

		/* TODO... this will be exit condition later*/
		if (strcmp(line, "exit\n") == 0)
		{
			free(line);
			return (0);
		};

		/*setup the argv array*/
		argv = setup_argv(argv);

		if (argv == NULL)
		{
			free(line);
			return (1);
		}

		/*split user's input*/
		split_line(line, argv);

        find_path_result = find_path(argv);
		
		if (find_path_result == 1)
		{
			cleanup_argv(argv);
			free(line);
			return (1);
		}

		execute_result = execute(argv);

		if (execute_result == 1) 
		{
			cleanup_argv(argv);
			free(line);
			return (1);
		}

		/*free all mallocs*/
		cleanup_argv(argv);
		free(line);
		line = NULL;
	}
	return (0);
}
