#include "main.h"

/**
 * split_search_path - splits path by delim to check for file in each directory
 * @argv: pointer to argv
 * Return: 0 on success 1 on failure
 */
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
		/*check for file in directory*/
		result = search_dir(argv, split_path);

		if (result == 0)
			return (0);

		split_path = strtok(NULL, delim);
	}
	return (1);
}


/**
 * search_dir - opens, reads and closes each directory
 *				looking for executable file
 * @argv: pointer to argv
 * @split_path: pointer to split_path
 * Return: 0 on success, 1 on failure
 */
int search_dir(argv_data_t *argv, char *split_path)
{
	DIR *dir;
	struct dirent *dir_struct;
	int result, close_check;
	char *temp;
	char buffer[1024];

	if (argv->args[0] == NULL)
		return (0);

	dir = opendir(split_path);

	if (dir == NULL)
		return (1);


	while ((dir_struct = readdir(dir)) != NULL)
	{
		result = strcmp(argv->args[0], dir_struct->d_name);

		if (result == 0)
		{
			temp = strdup(argv->args[0]);

			free(argv->args[0]);

			sprintf(buffer, "%s/%s", split_path, temp);

			argv->args[0] = strdup(buffer);

			free(temp);
			break;
		}
	}
	close_check = closedir(dir);

	if (close_check == -1 || result != 0)
		return (1);

	return (0);
}
