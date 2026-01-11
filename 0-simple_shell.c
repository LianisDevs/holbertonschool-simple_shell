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
