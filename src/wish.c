#include <limits.h>
#include "wish.h"
#include <signal.h>
#include<string.h>

int wish_exit = 0;

static void refuse_to_die(int sig)
{
  fputs("Type exit to exit the shell.\n", stderr);
}

static void prevent_interruption() {
  //fputs("SYSTEM GHOST: Hi, I am `prevent_interruption()`.\nSYSTEM GHOST: When I am implemented, I will install a signal handler,\nSYSTEM GHOST: and you won't be able to use Ctrl+C anymore :P\n", stderr);  
  struct sigaction sig;
  sig.sa_handler = refuse_to_die;
  if (sigaction(SIGINT, &sig, NULL) == -1) {
    perror("SIGACTION");
  }

}

int main(int argc, char *argv[])
{
  // These two lines make the macOS C compiler happy.
  // Otherwise, it complains about unused parameters.
  (void)argc;
  (void)argv;

  char path[PATH_MAX];
  char *home = getenv("HOME");

#ifdef DEBUG
  home = "."; // So that you could place the config into the CWD
#endif

  sprintf(path, "%s/%s", (home ? home : "."), WISH_CONFIG);
  wish_read_config(path, 1);
  
  prevent_interruption();
  while(!wish_exit) {
    fputs(WISH_DEFAULT_PROMPT, stdout);
    char *line = wish_read_line(stdin);
    if(line) {
      wish_parse_command(line);
      free(line);
    }

  }
  
  return EXIT_SUCCESS;
}

char *super_strdup(const char *s) {
  // Must be implemented
  // fputs("\nSYSTEM GHOST: did you just call unimplemented `super_strdup`?\n", stderr);
  char* target = strdup(s);
  if (!target) {
    abort();
  }
  return target;
}

void *super_malloc(size_t size) {
  // Must be implemented
  // fputs("\nSYSTEM GHOST: did you just call unimplemented `super_malloc`?\n", stderr);
  char *mal = malloc(size);
  if (!mal) {
    abort();
  }
  return mal;
}

void *super_realloc(void *ptr, size_t size) {
  // Must be implemented
  // fputs("\nSYSTEM GHOST: did you just call unimplemented `realloc`?\n", stderr);
  ptr = realloc(ptr, size);
  if (!ptr) {
    abort();
  }
  return ptr;
}

