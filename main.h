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

/**
 * struct argv_data - struct for argv to pass through the program
 * @args: pointer to pointer of chars
 * @position: int to move through args
 * @path: PATH from environ
 */
typedef struct argv_data
{
	char **args;
	int position;
	char *path;
} argv_data_t;

/**
 * struct queue - struct for command_queue to pass through the program
 * @commands: pointer to pointer of chars
 * @position: int to move through commands
 */
typedef struct queue
{
	char **commands;
	int position;
} command_queue_t;

/*setup functions*/
argv_data_t *setup_argv(argv_data_t *, command_queue_t *);
command_queue_t *setup_command_queue(command_queue_t *);

/*cleanup functions*/
void cleanup_argv(argv_data_t *);
void cleanup_command_queue(command_queue_t *);
void reset_argv(argv_data_t *, command_queue_t *, char *);

/*exit functions*/
void exit_success(argv_data_t *, command_queue_t *, char *);
void exit_general_error(argv_data_t *, command_queue_t *, char *);
void exit_command_not_found(argv_data_t *, command_queue_t *, char *);
void exit_command_failed(argv_data_t *, command_queue_t *, char *, int);

/*line functions*/
command_queue_t *read_line(command_queue_t *);
command_queue_t *read_line_non_interact(command_queue_t *);
void split_line(argv_data_t *, char *);
int valid_env(argv_data_t *, command_queue_t *, char *);
command_queue_t *proccess_command_queue(command_queue_t *);

/*path functions*/
int find_path(argv_data_t *, command_queue_t *, char *);
void get_path(argv_data_t *, command_queue_t *, char *);
int split_search_path(argv_data_t *);
int search_dir(argv_data_t *, char *);
int execute(argv_data_t *, command_queue_t *, char *);

/*built in function*/
void print_env(argv_data_t *, command_queue_t *, char *);
#endif
