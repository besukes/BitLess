/*  This module is about decompressing a file compressed using the code provided in this repository , 
it may (and most likely WILL) NOT WORK on a file compressed using other constructors.
    This module expects the file to have a header in the following format :
        ------------------------------
            LAST RELEVANT BITS (1 BYTE)
            FREQUENCY TABLE
            end
        ------------------------------
    If the file does not contain this format , it will throw an error and will not execute.
    The decompression itself cannot be done as of now but i'll eventually add it to the main function as a
text argument that can be sent before the paths.
*/
#include "decompressor.h"
#define INVALID_PATH 1
#define NO_HEADER 2
#define INVALID_HEADER_FORMAT 3


/*Error handler for Decompression function*/
static int dc_error_handler(int flags){
    if(flags == INVALID_PATH){
        printf("[ERROR] Decompression was tried on a invalid path\n");
        return INVALID_PATH;
    }
    else if(flags == NO_HEADER){
        printf("[ERROR] The file provided by the path doesn't include a decompression header ,"
                "or includes one in an invalid format\n");
        return NO_HEADER;
    }
}

/*Reads the frequency table of a compressed file header and stores the information directly onto f_info*/
static void parseFrequencyTable(char * line , CompressInfo* f_info , int parser[MAX_SYMBOLS]){
    int i=0;
    while(line!='\0'){
        char symb = line[i];
        while(line[i] != '\0' && line[i] > '9' && line[i] < '0') i++;
        while(line[i] != '\0' && line[i] != ' ') parser[symb] = (parser[symb]*10) + (int)line[i++];

        while(line[i++] == ' ');
    }
}


/*Parses file header to store the information on each symbol that exists and keeps its frequency to calculate
the probability to then apply the Shannon-Fano's algorithm to decompress the file*/
static int readFileHeader(FILE* file,CompressInfo* f_info,int * lrb){
    char line[LINE_MAX];

    //Reads the last relevant bits in the last relevant byte , stored at the start of the header
    fgets(line,LINE_MAX,file);
    *lrb = (int)line[0];
    if(line[1] != '\n') return (INVALID_HEADER_FORMAT);

    //Reads the Frequency table of each symbol to reconstruct the probabilities table
    int parsing_error = 0;
    int parser[MAX_SYMBOLS] = {0};
    while(!strcontain(line,"end") && !parsing_error){
        parsing_error = (fgets(line,LINE_MAX,file) == NULL);
        parseFrequencyTable(line,f_info,parser);
    }
    if(parsing_error) return (INVALID_HEADER_FORMAT);

    //Still needs to implement Shannon-Fanno reverse algorithm
}

/*Decompresses the file back to normal given the information after the execution of Shannon-Fano's algorithm*/
static void decompressSF(FILE* ext_file ,CompressInfo* f_info){

}


/*Decompression function that grabs a compressed file and decompresses it back to normal */
int decompress_handler(char * path){
    CompressInfo f_info = init_compress_info();

    FILE * compressed_file = fopen(path,"r");
    if(compressed_file == NULL) return (dc_error_handler(INVALID_PATH));

    int lrb = 0; //Last relevant bits in the file on the last byte
    int is_compressed_file = readFileHeader(compressed_file,&f_info,&lrb);
    fclose(compressed_file);

    if(!is_compressed_file) return (dc_error_handler(NO_HEADER));
    
    compressed_file = fopen(path,"r");
    decompress(compressed_file,&f_info);
    return 0;
}