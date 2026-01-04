#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

void split_line(char *line, argv_data_t *argv)
{
	char *result;
	const char *delim = " \n";

	result = strtok(line, delim);

	if (!result)
		return;

	argv->args[argv->position] = strdup(result);

	while (result)
	{
		argv->position++;

		result = strtok(NULL, delim);

		if (result == NULL)
			argv->args[argv->position] = result;
		else
			argv->args[argv->position] = strdup(result);
	}
	return;
}
