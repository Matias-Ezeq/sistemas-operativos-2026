#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    
        for (int i = 0; i < 3; i++){
            printf(".");
            sleep(10);
        };
        printf("\x1b[1F"); // Move to beginning of previous line
        printf("\x1b[2K"); // Clear entire line
    

    return 0;
}