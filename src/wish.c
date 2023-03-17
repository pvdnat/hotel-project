#include <limits.h>
#include "wish.h"

int wish_exit;

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
  
  // This is just a skeleton for your convenience
  wish_exit=0;
  while (wish_exit==0) {
    fputs(WISH_DEFAULT_PROMPT, stdout);
    char *line = wish_read_line(stdin);
    // DZ: Wrong number of parameters
    // DZ: "Pass the value returned by wish_read_line() to wish_parse_command()."
    wish_parse_command();
    if(line)
      free(line);
  }
  
  return EXIT_SUCCESS;
}
