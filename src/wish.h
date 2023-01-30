#ifndef WISH_H
#define WISH_H

#include <stdio.h>
#include <stdlib.h>
//#include <signal.h>
//#include <unistd.h>
//#include <unistd.h>

#define WISH_MAX_INPUT 80 // really modest :)
#define WISH_DEFAULT_PROMPT "> "

char *wish_read_line(FILE *in);
int wish_read_config(char *fname, int ok_if_missing);

#endif
