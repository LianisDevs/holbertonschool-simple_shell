#include "main.h"

/**
 * split_line- splits line by delim and copies each split into args
 * @argv: pointer to argv
 * @line: pointer to line
 * Return: 0 on success 1 on failure
 */
void split_line(argv_data_t *argv, char *line)
{
	char *result;
	const char *delim = " \n";

	result = strtok(line, delim);

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
