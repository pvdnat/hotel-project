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

    // This is just a skeleton for your convenience
    //wish_read_line(stdin);
    //wish_read_config("wish.config", 1);


    printf("%s", WISH_DEFAULT_PROMPT);

    if (wish_read_line(stdin)!=NULL) {
        printf("%s\n", "Success!!!");
        return EXIT_SUCCESS;
    } else {
        printf("%s\n", "Fail!!!");
        return EXIT_FAILURE;
    }
    
    /*
    if (wish_read_config("text.txt", 1)==0) {
        printf("%s\n", "Success!!!");
        return EXIT_SUCCESS;
    } else {
        printf("%s\n", "Fail!!!");
        return EXIT_FAILURE;
    }
    */

}
