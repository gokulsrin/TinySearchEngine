//need to create inside this file my pagesave function 
#include <stdio.h>
#include <stdlib.h>

void pagesave(char * url, int depth, char * content, int id){
    if(url != NULL && depth >= 0 && content != NULL && id >= 0){
        int length = snprintf( NULL, 0, "%d", id );
        char* str = malloc( length + 1 );
        snprintf( str, length + 1, "%d", id );
        FILE *fp = fopen(str, "W");
        free(str);
        fprintf(fp, "%s \n %d \n %s \n", url, depth, content);
        fclose(fp);
    }
    perror("Something has gone wrong");
}
