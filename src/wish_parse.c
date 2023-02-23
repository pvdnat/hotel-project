#include <stdio.h>
#include "wish.h"

// https://en.wikipedia.org/wiki/Escape_sequences_in_C#Table_of_escape_sequences
char *wish_unquote(char * s) {
  char *buffer[WISH_MAX_INPUT+1];

  int ch = 0, pos = 0;

  do {
    //check character after each backslash
    if (s[ch] == '\\') {
      switch (s[ch+1]) {
        case 'a':
          buffer[pos] = '\a';
          pos++;
          ch++;
          break;
        case 'b':
          pos--;
          ch++;
          break;
        case 'f':
          buffer[pos] = '\n';
          buffer[++pos] = '\t';
          pos++;
          ch++;
          break;
        case 'n':
          buffer[pos] = '\n';
          pos++;
          ch++;
          break;
        case 'r':
          buffer[pos] = '\r';
          pos++;
          ch++;
          break;
        case 't':
          buffer[pos] = '\t';
          pos++;
          ch++;
          break;
        case 'v':
          buffer[pos] = '\v';
          pos++;
          ch++;
          break;
        case '\'':
          buffer[pos] = '\'';
          pos++;
          ch++;
          break;
        case '"':
          buffer[pos] = '\"';
          pos++;
          ch++;
          break;
        case '?':
          buffer[pos] = '\?';
          pos++;
          ch++;
          break;
        default :
          buffer[pos] = '\\';
          pos++;
          break;
      }
      ch++;
    }
    buffer[pos] = line[ch];
    ch++;
    pos++;

  } while ( ch < strlen(s)+1 )

  //get new line
  char *line = malloc(strlen(buffer) + 1);
  strcpy(line, buffer);
  return line;
}

// Do not modify this function
void yyerror(const char* s) {
  fprintf(stderr, "Parse error: %s\n", s);
}

char *wish_safe_getenv(char *s) {
  return s;
}
