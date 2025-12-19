#ifndef MAIN_H
#define MAIN_H

extern char **environ;

typedef struct stat stat_t;

typedef struct argv_data
{
	char **args;
	int position;
} argv_data_t;

char *read_line(void);

argv_data_t *split_line(char *line);

int execute(argv_data_t *argv);

#endif
