#include <stdio.h>
#include <stdlib.h>
#include "main.h"

argv_data_t *setup_argv(argv_data_t *argv)
{
	argv = (argv_data_t *)malloc(sizeof(argv_data_t));

	if(!argv)
		return (NULL);

	argv->args = (char **)malloc(50 * sizeof(char *));

	if(!argv->args)
	{
		free(argv);
		return (NULL);
	}

	argv->position = 0;
	return (argv);
}

void cleanup_argv(argv_data_t *argv)
{
	argv->position = 0;

	while (argv->args[argv->position] != NULL)
	{
		free(argv->args[argv->position]);
		argv->position++;
	}
	free(argv->args);
	argv->args = NULL;

	free(argv);
	argv = NULL;

	return;
}
