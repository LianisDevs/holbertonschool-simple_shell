#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

argv_data_t *split_line(char *line)
{
	argv_data_t *argv;
	char *token;
	const char *delimiters = " \n";

	argv = (argv_data_t *) malloc(sizeof(argv_data_t));

	if (argv == NULL)
		return (NULL);

	argv->args = (char **)malloc(1024 * sizeof(char *));

	if (argv->args == NULL)
		return (NULL);

	argv->position = 0;

	token = strtok(line, delimiters);
	argv->args[argv->position] = strdup(token);
	argv->position++;

	while (token != NULL)
	{
		token = strtok(NULL, delimiters);
		if (token == NULL)
			break;

		argv->args[argv->position] = strdup(token);
		argv->position++;
	}
	argv->position = 0;
	return (argv);
}
