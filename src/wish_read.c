#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "wish.h"

char *wish_read_line(FILE *in) {
  char buffer[WISH_MAX_INPUT + 2] = ""; // truncate the buffer

  // Get a string and check its length
  fgets(buffer, WISH_MAX_INPUT + 2, in);
  if(strlen(buffer) > WISH_MAX_INPUT) {
    fputs("wish: line too long\n", stderr);

    // Clean the rest of the line
    int c = fgetc(in);
    while (c != '\n' && c != '\r' && c != EOF)
      c = fgetc(in);
    return NULL;
  }

  // Trim the line
  strtok(buffer, "\n");

  // Check the line for being blank
  for(size_t i = 0; i < strlen(buffer); ++i) {
    if(!isspace(buffer[i])) {
      // Allocate memory
      char *line = malloc(strlen(buffer) + 1);
      if (!line) // Too bad
	abort();
      strcpy(line, buffer);
      return line;
    }
  }

  return NULL;
}

int wish_read_config(char *fname, int ok_if_missing) {
  FILE *config;

  // Check if the file exists
  if(!(config = fopen(fname, "r"))) {
    if (ok_if_missing)
      return 0;
    // Report missing
    perror(fname);
    return 1;
  }

  // Read the file line by line
  while(!feof(config)) {
    char *line = wish_read_line(config);
    if(line) {
#ifdef DEBUG
      fprintf(stderr, "DEBUG: %s\n", line); // Only for debugging
#endif
      wish_parse_command(line);
      free(line);
    }
  }

  fclose(config);
  return 0;
}
