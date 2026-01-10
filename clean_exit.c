#include "main.h"

void clean_exit_success(argv_data_t *argv)
{
	argv = cleanup_argv(argv);
	exit(EXIT_SUCCESS);
}

void clean_exit_general(argv_data_t *argv)
{
	argv = cleanup_argv(argv);
	exit(EXIT_FAILURE);
}

void clean_exit_command_not_found(argv_data_t *argv)
{
	fprintf(stderr, "./hsh: 1: %s: not found\n", argv->args[0]);
	cleanup_argv(argv);
	exit(127);
}
