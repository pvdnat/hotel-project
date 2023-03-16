#pragma once
#include <stdio.h>
#include <stdlib.h>

#define DEBUG

#define WISH_MAX_INPUT 80 // really modest :)
#define WISH_DEFAULT_PROMPT "> "
#define WISH_CONFIG "wish.conf"

char *wish_read_line(FILE *in);
int wish_read_config(char *fname, int ok_if_missing);
char *wish_unquote(char * s);
int wish_parse_command(char *command);
extern int wish_exit;

// "Safe" memory handling functions
char *super_strdup(const char *s);
void *super_malloc(size_t size);
void *super_realloc(void *ptr, size_t size);

// Actual shell functions and data types

// An array of arguments, eventually NULL-terminated
typedef struct {
  int size;
  char **args;
} arglist_t;

// I/O redirection, as in "foobar < foo > bar"
typedef struct {
  char *in, *out1, *out2; // stdin, stdout-write, stdout-append
} redirection_t;

typedef struct prog prog_t; // Forward declaration

// The program to be executed
typedef struct prog {
  arglist_t args; // Arguments, including the program name
  redirection_t redirection; // Optional redirections
  prog_t *prev; // The previous program in the pipeline, if any; NULL otherwise
} prog_t;

prog_t *last_exe(prog_t *exe);
arglist_t create_arglist(char *arg);
arglist_t add_to_arglist(arglist_t al, char *arg);
prog_t *create_program(arglist_t al);

int spawn(prog_t *exe, int bgmode);
void free_memory(prog_t *exe, prog_t *pipe);

void yyerror(const char* s);

