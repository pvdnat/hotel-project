#include "wish.h"

int main(int argc, char *argv[])
{
  // These two lines make the macOS C compiler happy.
  // Otherwise, it complains about unused parameters.
  argc = 0;
  argv = NULL;
  
  // This is just a skeleton for your convenience
  wish_read_line(stdin);
  wish_read_config("wish.config", 1);
  
  return EXIT_SUCCESS;
}
