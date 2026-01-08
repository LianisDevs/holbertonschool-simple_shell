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

typedef struct argv_data
{
	char **args;
	int position;
	char *path;
} argv_data_t;

typedef struct command_queue
{
	char **commands;
	int position;
} command_queue_t;

command_queue_t *read_line(command_queue_t *command_queue);

command_queue_t *split_input_for_queue(command_queue_t *command_queue);

void split_line(char *line, argv_data_t *argv);

argv_data_t *setup_argv(argv_data_t *argv);

command_queue_t *setup_command_queue(command_queue_t *command_queue);

void cleanup_argv(argv_data_t *argv);

void cleanup_command_queue(command_queue_t *command_queue);

int execute(argv_data_t *argv);

int find_path(argv_data_t *argv);

void get_path(argv_data_t *argv);

int split_search_path(argv_data_t *argv);

int search_dir(char *split_path, argv_data_t *argv);
#endif
