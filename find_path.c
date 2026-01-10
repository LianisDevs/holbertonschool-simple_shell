#include "main.h"

int find_path(argv_data_t *argv)
{
	int result;
	

	get_path(argv);
	if (argv->path == NULL)
		return (1);

	result = split_search_path(argv);
	if (result == 1)
		return (1);

	return (0);
}

/**
 * get_path - own version of getenv. Searches through environ for PATH string
 * Return: if PATH is found return PATH else return NULL
 */ 
void get_path(argv_data_t *argv)
{
	int is_path;
	int i;
	size_t n = 5;
	char *path, *path_copy;
	const char *delim = "=";

	i = 0;
	while(environ[i] != NULL)
	{
		/*comparing i element in environ array for PATH= which is n size since we don't care at this stage about the rest of the PATH string*/
		is_path = strncmp(environ[i], "PATH=", n);

		/* PATH= string found*/
		if (is_path == 0)
		{
			path_copy = strdup(environ[i]);

			/*this gives us just PATH before the =, need to call strtok again*/
			path = strtok(path_copy, delim);

			if (strcmp(path, "PATH") != 0)
			{
				free(path_copy);
				return;
			}

			/*this gives us the string after the =, actual path we want to return*/
			path = strtok(NULL, delim);

			if (path != NULL)
			{
				if (strcmp(path, "") == 0)
				{
					free(path_copy);
					argv->path = NULL;
					return;
				}
				argv->path = strdup(path);
			}
			free(path_copy);
			return;
		}
		i++;
	}
	return;
}

int valid_env(argv_data_t *argv, command_queue_t *command_queue, char *line)
{
	int is_path;
	int i;
	size_t n = 5;
	stat_t statbuff;
	
	if (stat(argv->args[0], &statbuff) != -1)
	{
		return (0);
	}
	i = 0;
	while(environ[i] != NULL)
	{
		/*comparing i element in environ array for PATH= which is n size since we don't care at this stage about the rest of the PATH string*/
		is_path = strncmp(environ[i], "PATH=", n);

		/* PATH= string found*/
		if (is_path == 0)
			return (1);

		i++;
	}

	fprintf(stderr, "./hsh: 1: %s: not found\n", argv->args[0]);
	cleanup_argv(argv);
	cleanup_command_queue(command_queue);
	free(line);
	exit (127);
}
