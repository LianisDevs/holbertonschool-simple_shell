#include "main.h"

void split_line(argv_data_t *argv)
{
	char *result;
	const char *delim = " \n";


	result = strtok(argv->line, delim);

	if (!result)
	{
		argv->args[0] = NULL;
		return;
	}

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
}
