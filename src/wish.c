#include <stdio.h>
#include <stdlib.h>
//#include <signal.h>
#include <unistd.h>
#include <ctype.h>
#include "wish.h"

int main(int argc, char *argv[]) {
    // These two lines make the macOS C compiler happy.
    // Otherwise, it complains about unused parameters.
    argc = 0;
    argv = NULL;

    char *file_name;                            
    printf("%s%s", WISH_DEFAULT_PROMPT, "wish: enter the file name: ");
    file_name = wish_read_line(stdin);

    if (file_name != NULL) {
        //printf("%s%s\n\n", WISH_DEFAULT_PROMPT, "wish: the file contains lines...");
        if (wish_read_config(file_name, 1)==0) {
            printf("%s%s\n\n", WISH_DEFAULT_PROMPT, "wish: reading file...");
            printf("\n%s%s\n", WISH_DEFAULT_PROMPT, "wish: successfully read the file!!!");
            return EXIT_SUCCESS;
        } else {
            printf("\n%s%s\n", WISH_DEFAULT_PROMPT, "wish: file not exists!");
            return EXIT_FAILURE;
        }
    } 
    
}
