#include <stdio.h>
#include "wish.h"

// https://en.wikipedia.org/wiki/Escape_sequences_in_C#Table_of_escape_sequences
char *wish_unquote(char * s) {
  return s; // MODIFY!
}

// Do not modify this function
void yyerror(const char* s) {
  fprintf(stderr, "Parse error: %s\n", s);
}

char *wish_safe_getenv(char *s) {
  return s;
}
