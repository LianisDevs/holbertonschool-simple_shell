#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"

char *read_line(char *line)
{
	size_t length = 0;
	if (isatty(0) == 1)
		printf("$ ");

	if (getline(&line, &length, stdin) == -1)
	{
		free(line);
		line = NULL;
		return (NULL);
	};

	return (line);
}
