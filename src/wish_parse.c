#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "wish.h"

// https://en.wikipedia.org/wiki/Escape_sequences_in_C#Table_of_escape_sequences
char *wish_unquote(char * s) {
  int i, j;
  for (i = 0, j = 0; s[i]; ++i, ++j) {
    if(s[i] == '\\') {
      switch(s[++i]) {
      case 'a': s[j] = '\a'; break;
      case 'b': s[j] = '\b'; break;
      case 'f': s[j] = '\f'; break;
      case 'n': s[j] = '\n'; break;
      case 'r': s[j] = '\r'; break;
      case 't': s[j] = '\t'; break;
      case 'v': s[j] = '\v'; break;
      case '\\': s[j] = '\\'; break;
      case '\'': s[j] = '\''; break;
      case '"': s[j] = '"'; break;
      default:
	fprintf(stderr, "Invalid escape sequence\n");
	s[j] = 0;
	return s;
      }
    } else { //Simply copy
      s[j] = s[i];
    }
  }
  s[j] = 0; // NULL-terminate the string
  return s; 
}

// Do not modify this function
void yyerror(const char* s) {
  fprintf(stderr, "Parse error: %s\n", s);
}

char *wish_safe_getenv(char *name) {
  static char *empty = "";
  char *var = getenv(name);  
  if (var)
    return var;
  else
    return empty;
}

void wish_assign(char *name, char *value) {
  if(setenv(name, value, 1))
    perror(name);
  free(name);
  free(value);
}

// Find the first program on the command line
prog_t *last_exe(prog_t *exe) {
  while(exe->prev) exe = exe->prev;
  return exe;
}

// All these implementations are silly but they work
arglist_t add_to_arglist(arglist_t al, char *arg)
{
  al.size++;      // Increase argument array size
  al.args = super_realloc(al.args, sizeof(char*) * al.size); // Add storage
  al.args[al.size - 1] = arg;  // Add the last element
  return al;
}

arglist_t create_arglist(char *arg)
{
  arglist_t al;
  al.args = super_malloc(sizeof(char*)); // New argument array
  al.args[0] = arg; // Its first element
  al.size = 1;
  return al;
}

prog_t *create_program(arglist_t al)
{
  prog_t *p = super_malloc(sizeof(prog_t));
  p->args = al;
  p->redirection.in = p->redirection.out1 = p->redirection.out2 = NULL;
  p->prev = NULL;
  return p;
}

int handle_child(pid_t pid, int bgmode)
{
  if(!bgmode) {
    int wstatus;
    if (-1 == waitpid(pid, &wstatus, 0)) {
      perror("waitpid");
      return 1;
    }
    
    if (WIFEXITED(wstatus)) {
      char value[16];
      snprintf(value, sizeof value, "%d", WEXITSTATUS(wstatus));
      if(setenv("_", value, 1))
	return 1;
    } else
      return 1;    
  }
  return 0;
}

// "Rename" fule descriptor "old" to "new," if necessary. After the
// execution of this function a program that "believes" that it uses
// the "old" descriptor (e.g., stdout #1 for output) will be actually
// using the "new" descriprot (e.g., an outgoinf pipe).  This
// functions terminates the process of error and should not be used in
// the parent, only in a child.
static void dup_me (int new, int old) {
  if (new != old && -1 == dup2(new, old)) {
    perror("dup2");
    exit(1);
  }
}

// Execute the program defined in "exe"
static void start(prog_t *exe) {
  arglist_t args = exe->args;
  args.args = super_realloc(args.args, sizeof(char*) * (args.size + 1));
  args.args[args.size] = (char*)NULL;
  execvp(args.args[0], args.args);
  perror(args.args[0]);
}

int spawn(prog_t *exe, int bgmode)
{
  /*
    typedef struct prog {
    arglist_t args; // Arguments, including the program name
    ...
    } prog_t;

    typedef struct {
    int size;
    char **args;
    } arglist_t;    
  */

  pid_t pid;
  switch(pid = fork()) {
  case -1:
    perror("fork");
    return 1;
    
  case 0: // Child
    start(exe);
    _exit(EXIT_FAILURE); // Do NOT use exit()!
    
  default: // Parent
    return handle_child(pid, bgmode);
  }
}

// Find the number of programs on the command line
static size_t cmd_length(prog_t *exe) {
  int count = 0;
  while(exe) {
    exe = exe->prev;
    count++;
  }
  return count;
}

void free_memory(prog_t *exe)
{
  for(int i = 0; i < exe->args.size; i++)
    free(exe->args.args[i]);
  free(exe->args.args);
  if(exe->redirection.in)
    free(exe->redirection.in);
  if(exe->redirection.out1)
    free(exe->redirection.out1);
  if(exe->redirection.out2)
    free(exe->redirection.out2);
  free (exe);
}

