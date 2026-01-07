#include "main.h"

/**
* read_line -
* @line: 
* Return: line or NULL on failure
*/

char *read_line(char *line)
{
	size_t length = 0;

	/*checking if tty to print $*/
	if (isatty(0) == 1)
		printf("$ ");

	if (getline(&line, &length, stdin) == -1)
	{
		/*if getline fails then free and return*/
		free(line);
		line = NULL;
		return (NULL);
	}
	return (line);
}
