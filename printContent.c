#include "print.h"
void printContent(FILE* fptr){
    fseek(fptr,0,SEEK_SET);
    char* data=(char*) malloc(1000*sizeof(char));
    while (fgets(data,1000,fptr)!=NULL){
        printf("%s",data);
    }
    free(data);
}
