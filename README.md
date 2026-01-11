# SIMPLE SHELL

This repo contains all the files to run a simple UNIX command-line interpreter/ simple shell. This program replicates the basic functionalities of a standard shell like sh or bash. Completed as the final project for Holberton School- Sprint 1 Programming in C.

---
### Table of Contents

- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Files](#files)
- [Authors]((#authors)

---
### Features {#features}
- Display a prompt and wait for user input
- Execute built-in commands like exit and env
- Execute system commands found in PATH
- Handle command arguments
---
### Requirements {#requirements}
- All C files in this directory are compiled using gcc -Wall -Werror -Wextra -pedantic -std=gnu89
---
### Installation {#installation}

1. Clone the repository to your 
```
git clone https://github.com/LianisDevs/holbertonschool-simple_shell
```

2. Navigate to this directory
```
cd holbertonschool-simple_shell
```

3. Compile the source files:
```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```
---
### Usage {#usage}

1. Run program in interactive mode
```
./hsh
```
2. Use system commands like:
```
ls -l
pwd
```
or built-in commands like:
```
exit 
env
```
---
### Files {#files}

* 0-simple_shell.c 
    This is the main file for this program. Contains main() forever while loop to run the shell. Breaks out of forever while loop if not in interative mode 

* argv.c

    1.  setup_argv() prepares argv data structure memory and sets fields. if malloc fails, exits program wih failure
    2.  cleanup_argv() frees memory malloced for fields inside argv data structure and frees argv
    3.  reset_argv() called in process_command_queue() to free all memory to do with argv data structure so it's ready for the next iteration in process_command_queue()

* clean_exit.c

    1.  exit_success() frees all malloced memory to ensure no memory leaks, exits program with success 
    2.  exit_general_error() frees all malloced memory to ensure no memory leaks, exits program with failure
    3.  exit_command_not_found() prints command not found message to terminal. Frees all malloced memory to ensure no memory leaks, exits program with status 127
    4.  exit_command_failed() frees all malloced memory to ensure no memory leaks, exits program with status from fork

* command_queue.c

    1.  setup_command_queue()  prepares command_queue data structure memory and sets fields. If malloc fails, exits program with failure
    2.  cleanup_command_queue() frees memory malloced for fields inside command_queue data structure and command_queue
    3.  process_command_queue() to ensure that commands entered by the user are executed in order.
        Starting at command_queue->commands[0] the commands are taken 1 at a time through the function, if the command is "exit" exits program with success.
        if the command is "env" print_env() and increment command_queue to go to next command.
        Otherwise split_line() if the first args is empty in argv, reset_argv() and continue to the next command in command_queue. 
        If the first arg contains values, valid_env() to check for valid environ. If found, find_path() to search through directories for executable.
        If found, execute() to execute the command on a fork. After successful execution of the command, reset_argv() and iterate to the next position in the command_queue.
        Continue this process until no commands left. 

* execute.c

    1. execute() creates a fork to exectue the valid command on so that the program doesn't exit when this command is executed.
    If command not executed, exit program with exit_command_failed

* find_path.c

    1.  find_path() searches through all directories in PATH for desired executable. If not found exit program exit_command_not_found
    2.  get_path()  own version of getenv()
    3.  valid_env() looks for the PATH variable by searching through each element in the global environ variable. If not found exit program exit_command_not_found()

* main.h
    Header file for program. Contains libraries and declarations for data structures and functions

* print_env.c
    1. print_env() increments through the environ and prints. After printing all of the environ reset_argv().

* readline.c

    1.  read_line() gets the user's input. Checks if the program is TTY- interactive mode. If not readline_non_interact() is called.
        Prints prompt and if user input is not an empty line stores it in command_queue
    2.  readline_non_interact() non-interactive mode stores all of user input in command_queue. Empty lines are ignored

* search_path.c

    1.  split_search_path() splits the PATH by : checking each directory for the file with search_dir()
    2   search_dir() opens, reads and closes directory checking for executable file

* split_line.c

    1.  split_line() takes the command and splits the line by spaces and newlines and putting each split in args
---
### Authors {#authors}

Liani Mckeown <lianisdevs@gmail.com>
---
