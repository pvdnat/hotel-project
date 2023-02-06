#include <stdio.h>
#include <stdlib.h>
//#include <signal.h>
#include <unistd.h>
#include <ctype.h>
#include "wish.h"


char *wish_read_line(FILE *in) {

  int buffer_length = 2048, count = 0;
  char *buffer = (char *)malloc(sizeof(char) * buffer_length);
  if (buffer==NULL) {
    perror("Error: ");
  }

  char str[WISH_MAX_INPUT];

  while (fgets(str, WISH_MAX_INPUT, in) != NULL) {
    if (count == buffer_length) {
      buffer_length *= 2;
      buffer = realloc(buffer, buffer_length);
      if (buffer == NULL) {
        perror("Error: ");
      }
    }

    if (strchr(str, '\n') != NULL) {
      if (!isspace((int)*str)) {
        str[strcsp(str, '\n')] = 0;
        strcpy((buffer+count), str);
        count++;
      } else {
        return NULL;
      }
    } else {
      while (strchr(str, '\n') == NULL) {
        fgets(str, WISH_MAX_INPUT, in);
      }
      printf("wish: line too long");
      fgets(str, WISH_MAX_INPUT, in);
      return NULL;
    }
  }

  return buffer;
}

int wish_read_config(char *fname, int ok_if_missing) {
  FILE *f;
  f = fopen(fname, 'r');
  if (f == NULL && ok_if_missing != 1) {
    perror("Error: ");
    return 0;
  } else if (f!=NULL) {
    wish_read_line(f );
    return 1;
  }
  fclose(f);
}
