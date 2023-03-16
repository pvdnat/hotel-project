//#include <stdio.h>// DZ: !!!
//#include <stdlib.h>// DZ: !!!
//#include <signal.h>
//#include <unistd.h> // DZ: !!!
//#include <ctype.h>// DZ: !!!
#include "wish.h"

// DZ: None of this makes sense
int main(int argc, char *argv[]) {
    // These two lines make the macOS C compiler happy.
    // Otherwise, it complains about unused parameters.
    argc = 0;
    argv = NULL;

    char *file_name;
    // DZ: Why???
    printf("%s%s", WISH_DEFAULT_PROMPT, "wish: enter the file name: ");
    file_name = wish_read_line(stdin);

    if (file_name != NULL) {
      // DZ: Clean "trash code" before submitting
        //printf("%s%s\n\n", WISH_DEFAULT_PROMPT, "wish: the file contains lines...");
        if (wish_read_config(file_name, 1)==0) {
	  // DZ: Why???
          printf("%s%s\n\n", WISH_DEFAULT_PROMPT, "wish: reading file...");
	  // DZ: Why???
	  printf("\n%s%s\n", WISH_DEFAULT_PROMPT, "wish: successfully read the file!!!");
            return EXIT_SUCCESS;
        } else {
	  // DZ: Why???
            printf("\n%s%s\n", WISH_DEFAULT_PROMPT, "wish: file not exists!");
            return EXIT_FAILURE;
        }
    } 
    
}
