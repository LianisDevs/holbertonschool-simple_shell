#include <stdio.h>
#include <stdlib.h>
#include "main.h"

char *read_line(void)
{
	char *line = NULL;
	size_t length = 0;

	if (getline(&line, &length, stdin) == -1)
	{
		if (feof(stdin)) /*don't know if I can use feof*/
			exit(EXIT_SUCCESS);
		else
		{
			perror("readline");
			exit(EXIT_FAILURE);
		}
	}
	return (line);
}
