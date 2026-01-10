#include "main.h"

int split_search_path(argv_data_t *argv)
{
	char *split_path;
	const char *delim = ":";
	int result;

	split_path = strtok(argv->path, delim);
	if (!split_path)
		return (1);

	while (split_path)
	{
		/* need to check for file in split_path*/
		result = search_dir(split_path, argv);

		if (result == 0)
			return (0);

		split_path = strtok(NULL, delim);
	}
	return (1);
}

int search_dir(char *split_path, argv_data_t *argv)
{
	DIR *dir;
	struct dirent *dir_struct;
	int result, close_check;
	char *temp;
	char buffer[1024];
	stat_t sb;

	dir = opendir(split_path);

	if (dir == NULL)
		return (1);

	while ((dir_struct = readdir(dir)) != NULL)
	{
		if ((result = strcmp(argv->args[0], dir_struct->d_name)) == 0)
		{
			temp = strdup(argv->args[0]);
			
			free(argv->args[0]);

			sprintf(buffer, "%s/%s", split_path, temp);

			if (stat(buffer, &sb) == -1)
				clean_exit_command_not_found(argv);

			argv->args[0] = strdup(buffer);

			free(temp);
			break;
		}
	}

	if ((close_check = closedir(dir)) == -1)
		return (1);

	if (result != 0)
		return (1);

	return (0);
}
