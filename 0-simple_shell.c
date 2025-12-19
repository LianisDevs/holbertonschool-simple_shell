#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/**
 * READ- shell reads a line of input from stdin using getline
 *
 * PARSE- input string is broken down into a command and its arguments (tokens) using strtok
 * 	- tokens are stored in an array of strings
 *
 * EXECUTE- shell interprets the command
 * 	  - create a new prtocess to run the program
 *
 * LOOP- process repeats until the user exits the shell
 *
 */


int main(void)
{
	char *line = NULL;
	int status = 1;
	argv_data_t *argv;

	do {
		/*print prompt*/
		printf("$ ");

		/*call function to read line*/
		line = read_line();

		if (line == NULL)
			return (1);

		/*call function to split the line into arguments/ tokens*/
		argv = split_line(line);

		/*
		 * call a function to execute the args/tokens
		 * return value is stored in status which will determine when to exit
		 */
		status = execute(argv);
		if (status == 0)
			return (1);

		free(line);
		argv->position = 0;
		while (argv->args[argv->position] != NULL)
		{
			free(argv->args[argv->position]);
			argv->position++;
		}
		free(argv->args);
		free(argv);
	} while (status);

	return (0);
}
