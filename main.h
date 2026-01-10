#ifndef MAIN_H
#define MAIN_H

#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

extern char **environ;

typedef struct stat stat_t;

typedef struct queue
{
	char **commands;
	int position;
} command_queue_t;

typedef struct argv_data
{
	char **args;
	int position;
	char *path;
	char *line;
	command_queue_t *command_queue;
} argv_data_t;

/*setup functions*/
argv_data_t *setup_argv(argv_data_t *);
argv_data_t *setup_command_queue(argv_data_t *);

/*handle input functions*/
argv_data_t *read_line(argv_data_t *);
void split_line(argv_data_t *);

int find_path(argv_data_t *);
void get_path(argv_data_t *);
void valid_env(argv_data_t *);

int execute(argv_data_t *);

int split_search_path(argv_data_t *);
int search_dir(char *, argv_data_t *);

/*cleanup functions: */

argv_data_t *cleanup_argv(argv_data_t *);
command_queue_t *cleanup_command_queue(argv_data_t *);
argv_data_t *reset_argv(argv_data_t *);

void argv_printer(argv_data_t *argv);

void clean_exit_success(argv_data_t *);
void clean_exit_general(argv_data_t *);
void clean_exit_command_not_found(argv_data_t *);
#endif
