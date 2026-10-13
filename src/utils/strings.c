#include <stdio.h>
#include <stdlib.h>

/*Checks the length of a string*/
int strlent(char * str){
    int i=0;
    for(;str[i]!='\0';i++);
    return i;
}

/*Appends zip right before the format specification for the file (before the .)*/
void append_zip(char *orig,char* dest){
    if(orig == NULL) return;
    int i=0 , j = 0;

    for(;orig[i]!='.' && orig[i]!='\0';i++) dest[i] = orig[i];
    dest[i] = '_';
    dest[i+1] = 'z';
    dest[i+2] = 'i';
    dest[i+3] = 'p';

    for(j=i+4;orig[i]!='\0';j++,i++) dest[j] = orig[i];
    dest[j] = '\0';
}

/*Checks if a string CONTAINER contains a CONTEDED string at its begging*/
int strcontain(char * container , char * contended){
    int i;
    for(i=0;contended[i] != '\0' && container[i] != '\0' && container[i] == contended[i];i++);
    return(contended[i] == '\0');
}