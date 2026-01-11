# SIMPLE SHELL

This repository contains all the files to run a simple UNIX command-line interpreter/ simple shell. This program replicates the basic functionalities of a standard shell like sh or bash. Completed as the final project for Holberton School- Sprint 1 Programming in C.

---

### Table of Contents

- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Files](#files)
- [Author](#author)

---

### Features
- Display a prompt and wait for user input
- Execute built-in commands like exit and env
- Execute system commands found in PATH
- Handle command arguments

---

### Requirements
- All C files in this directory are compiled using gcc -Wall -Werror -Wextra -pedantic -std=gnu89

---

### Installation

1. Clone the repository to your 
```
>  git clone https://github.com/LianisDevs/holbertonschool-simple_shell
```

2. Navigate to this directory
```
>  cd holbertonschool-simple_shell
```

3. Compile the source files:
```
>  gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

---

### Usage

* Run program in interactive mode
```
>  ./hsh
```
Use system commands like:
```
(:  ls -l
(:  pwd
```
or built-in commands like:
```
(:  exit 
(:  env
```
* Run program in non-interactive mode with system and/or built-in commands

Multiple commands:
```
>  echo "ls
>  env
>  pwd" | ./hsh
```
Single commands:
```
>  echo "ls -l" | ./hsh
```

---

### Files

* 0-simple_shell.c 
    This is the main file for this program. Contains main() forever while loop to run the shell. Breaks out of forever while loop if not in interative mode 

* argv.c

    *   setup_argv() prepares argv data structure memory and sets fields. if malloc fails, exits program wih failure
    *   cleanup_argv() frees memory malloced for fields inside argv data structure and frees argv
    *   reset_argv() called in process_command_queue() to free all memory to do with argv data structure so it's ready for the next iteration in process_command_queue()

* clean_exit.c

    *   exit_success() frees all malloced memory to ensure no memory leaks, exits program with success 
    *   exit_general_error() frees all malloced memory to ensure no memory leaks, exits program with failure
    *   exit_command_not_found() prints command not found message to terminal. Frees all malloced memory to ensure no memory leaks, exits program with status 127
    *   exit_command_failed() frees all malloced memory to ensure no memory leaks, exits program with status from fork

* command_queue.c

    *   setup_command_queue()  prepares command_queue data structure memory and sets fields. If malloc fails, exits program with failure
    *   cleanup_command_queue() frees memory malloced for fields inside command_queue data structure and command_queue
    *   process_command_queue() to ensure that commands entered by the user are executed in order.
        Starting at command_queue->commands[0] the commands are taken 1 at a time through the function, if the command is "exit" exits program with success.
        if the command is "env" print_env() and increment command_queue to go to next command.
        Otherwise split_line() if the first args is empty in argv, reset_argv() and continue to the next command in command_queue. 
        If the first arg contains values, valid_env() to check for valid environ. If found, find_path() to search through directories for executable.
        If found, execute() to execute the command on a fork. After successful execution of the command, reset_argv() and iterate to the next position in the command_queue.
        Continue this process until no commands left. 

* execute.c

    *   execute() creates a fork to exectue the valid command on so that the program doesn't exit when this command is executed.
        If command not executed, exit program with exit_command_failed

* find_path.c

    *   find_path() searches through all directories in PATH for desired executable. If not found exit program exit_command_not_found
    *   get_path()  own version of getenv()
    *   valid_env() looks for the PATH variable by searching through each element in the global environ variable. If not found exit program exit_command_not_found()

* main.h
    Header file for program. Contains libraries and declarations for data structures and functions

* print_env.c
    *  print_env() increments through the environ and prints. After printing all of the environ reset_argv().

* readline.c

    *   read_line() gets the user's input. Checks if the program is TTY- interactive mode. If not readline_non_interact() is called.
        Prints prompt and if user input is not an empty line stores it in command_queue
    *   readline_non_interact() non-interactive mode stores all of user input in command_queue. Empty lines are ignored

* search_path.c

    *   split_search_path() splits the PATH by : checking each directory for the file with search_dir()
    *   search_dir() opens, reads and closes directory checking for executable file

* split_line.c

    *   split_line() takes the command and splits the line by spaces and newlines and putting each split in args
---

### Author 

* Liani Mckeown <lianisdevs@gmail.com>

---
