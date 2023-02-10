#include <stdio.h>
#include <stdlib.h>
//#include <signal.h>
#include <unistd.h>
#include <ctype.h>
#include "wish.h"

// Check if line is empty
int isempty(char *buffer) {
    while (*buffer != '\0') {
        if (!isspace((int)*buffer)) 
            return 0;
        buffer++;
    }
    return 1;
}

char *wish_read_line(FILE *in) {
    // Define buffer and its length
    int buffer_length = WISH_MAX_INPUT +2;          // Space for newline and endline characters
    char *buffer = (char *)malloc(sizeof(char) * buffer_length);
    if (buffer == NULL) {
        perror("wish: fail to allocate buffer memory");
        return NULL;
    }

    // Get the line and check with condition
    if (fgets(buffer, buffer_length, in) != NULL) {
        if (!isempty(buffer)) {                       // Check if line is empty
            if (strchr(buffer, '\n') == NULL) {             // Check if reach end of line
                while (strchr(buffer, '\n') == NULL) {      // Discard the whole line if longer    
                    fgets(buffer, buffer_length, in);       //than max length 
                }
                fprintf(stderr, "%s\n", "wish: line too long");
                return NULL;
            }
            buffer[strcspn(buffer, "\n")] = 0;              // Remove newline character
            return buffer;
        }
    }
    return NULL;
}

int wish_read_config(char *fname, int ok_if_missing) {
    FILE *f;
    f = fopen(fname, "r");

    // Check if file exist and read it
    if (f == NULL && ok_if_missing != 1) {
        perror("wish error: file not exists");
        return 1;
    } else if (f!=NULL) {
        while (!feof(f)) {
            //printf("%s\n", wish_read_line(f));              // Temporary print line that read
            wish_read_line(f);
        }
        return 0;
    }
    fclose(f);
    return 1;
}
