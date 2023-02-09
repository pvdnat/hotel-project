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

    char *dir = getenv("USERPROFILE");          // Get the USER directory for testing 
    char *file_name;                            //since my getenv("HOME") return NULL
    strcat(dir,"\\hotel-project\\src\\");       // Where the testing text file at

    printf("%s%s", WISH_DEFAULT_PROMPT, "wish: enter the file name: ");
    file_name = wish_read_line(stdin);
    printf("%s%s\n\n", WISH_DEFAULT_PROMPT, "wish: reading file...");
    
    if (file_name != NULL) {
        strcat(dir, file_name);
        printf("%s%s\n\n", WISH_DEFAULT_PROMPT, "wish: the file contains lines...");
        
        if (wish_read_config(dir, 1)==0) {
        printf("\n%s%s\n", WISH_DEFAULT_PROMPT, "wish: successfully read the file!!!");
        return EXIT_SUCCESS;
    } else {
        printf("\n%s%s\n", WISH_DEFAULT_PROMPT, "wish: failed to read file!!!");
        return EXIT_FAILURE;
        }
    }
}
