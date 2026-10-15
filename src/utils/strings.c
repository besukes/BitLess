#include <stdio.h>
#include <stdlib.h>

/*Checks the length of a string*/
int strlent(char * str){
    int i=0;
    for(;str[i]!='\0';i++);
    return i;
}

/*Appends a string right before the format specification for the file (before the .)*/
void append_before_format(char* orig,char* dest, char * append){
    if(orig == NULL) return;
    int i=0;
    int loop = 1;
    //Verifies if any of the folders leading to the file has a dot in it , if it has then it needs to continue the search
    while(loop){
        for(;orig[i]!='.' && orig[i]!='\0';i++) dest[i] = orig[i];

        if(orig[i] == '\0') loop = 0;
        else{
            int k;
            for(k=i+1;orig[k]!='\0' && orig[k]!= '.';k++);
            if(orig[k] == '.' && k!=i) i++; //If it finds a dot before \0 then the indx i doesnt have the format dot
            else loop = 0;
        }
    }
    int u;
    for(u=0;append[u]!='\0';u++)
        dest[i+u] = append[u];

    dest[i+u] = '\0';
}

/*Checks if a string CONTAINER contains a CONTEDED string at its begging*/
int strcontain(char * container , char * contended){
    int i;
    for(i=0;contended[i] != '\0' && container[i] != '\0' && container[i] == contended[i];i++);
    return(contended[i] == '\0');
}