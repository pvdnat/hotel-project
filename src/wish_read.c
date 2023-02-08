#include <stdio.h>
#include <stdlib.h>
//#include <signal.h>
#include <unistd.h>
#include <ctype.h>
#include "wish.h"


char *wish_read_line(FILE *in) {
    // Define buffer length and buffer counter 
    int buffer_length = 2048, count = 0;
    char *buffer = (char *)malloc(sizeof(char) * buffer_length);
    if (buffer==NULL) {
        perror("wish error: fail to allocate buffer memory");
        return NULL;
    }

    // Define string pointer */
    char str[WISH_MAX_INPUT];

    // Get the first line from the file and check if line exist 
    while (fgets(str, WISH_MAX_INPUT, in) != NULL) {

        // Check if buffer has enough memory and reallocate if needed 
        if (count == buffer_length) {
            buffer_length *= 2;
            buffer = realloc(buffer, buffer_length);
            if (buffer == NULL) {
                perror("wish error: fail to reallocate buffer memory");
                return NULL;
            }
        }


        // Check if end of line 
        if (strchr(str, '\n') != NULL) {
            if (!isspace((int)*str)) {            // Check if line is include empty 
                str[strcspn(str, "\n")] = 0;         // Remove newline character
                strcpy((buffer+count), str);
                count++;
            } else {
                return NULL;
            }

        // Discard the whole line that longer than max input 
        } else {
            while (strchr(str, '\n') == NULL) {   // Keep discarding until end of line 
                fgets(str, WISH_MAX_INPUT, in);
            }
            fprintf(stderr, "%s", "wish error: line too long\n");
            return NULL;
        }
    }
    return buffer;
}

int wish_read_config(char *fname, int ok_if_missing) {
    // Check if file exist and read it 
    FILE *f;
    f = fopen(fname, "r");
    if (f == NULL && ok_if_missing != 1) {
        perror("wish error: file not exists");
        return 1;
    } else if (f!=NULL) {
        if (wish_read_line(f) != NULL) {
            return 0;
        }
    }
    fclose(f);
    return 1;
}