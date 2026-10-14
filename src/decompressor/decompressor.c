/*  This module is about decompressing a file compressed using the code provided in this repository , 
it may (and most likely WILL) NOT WORK on a file compressed using other constructors.
    This module expects the file to have a header in the following format :
        ------------------------------
            LAST RELEVANT BITS (1 BYTE)
            Canonic TABLE
            end
        ------------------------------
    If the file does not contain this format , it will throw an error and will not execute.
    The decompression itself cannot be done as of now but i'll eventually add it to the main function as a
text argument that can be sent before the paths.
*/
#include "decompressor.h"
#define NO_ERRORS 0
#define INVALID_PATH 1
#define INVALID_HEADER_FORMAT 2
#define NO_PATH 3


/*Error handler for Decompression function*/
static int dc_error_handler(int flags , int indx){
    if(flags == INVALID_PATH){
        printf("[ERROR] Decompression was tried on a invalid path at index %d\n",indx);
        return (INVALID_PATH);
    }
    else if(flags == INVALID_HEADER_FORMAT){
        printf("[ERROR] The file provided by the path at position %d doesn't include a decompression header ,"
                "or includes one in an invalid format\n",indx);
        return (INVALID_HEADER_FORMAT);
    }
    else if(flags == NO_PATH){
        printf("[ERROR] No paths were included at run time\n");
        return (NO_PATH);
    }
    return 0;
}

/*Reads the frequency table of a compressed file header and stores the information directly onto f_info*/
static void parseCanonicTable(char * line , CompressInfo* f_info , int parser[MAX_SYMBOLS]){
    int i=0;
    while(*line!='\0'){
        unsigned char symb = (unsigned char)line[i];
        parser[symb] = line[i+1];
        i+=2;
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
        parseCanonicTable(line,f_info,parser);
    }
    if(parsing_error) return (INVALID_HEADER_FORMAT);

    //Still need to loop through the parser and do some memory allocations at the end
    //Also i need to grab each symbol and calculate every single symbol compressed code
}

/*Decompresses the file back to normal given the information after the execution of Shannon-Fano's algorithm*/
static void decompress(FILE* ext_file ,CompressInfo* f_info){

}


/*Decompression function that grabs a compressed file and decompresses it back to normal */
int decompress_handler(char * path){
    CompressInfo f_info = init_compress_info();

    FILE * compressed_file = fopen(path,"r");
    if(compressed_file == NULL) return (INVALID_PATH);

    int lrb = 0; //Last relevant bits in the file on the last byte
    int is_compressed_file = readFileHeader(compressed_file,&f_info,&lrb);
    fclose(compressed_file);

    if(!is_compressed_file) return (INVALID_HEADER_FORMAT);
    
    compressed_file = fopen(path,"r");
    decompress(compressed_file,&f_info);

    return (NO_ERRORS);
}


/* Main function that decompresses every path given to it at run time.*/
int main(int argc , char ** argv){
    if(argc < 2) return dc_error_handler(NO_PATH,0);
    CompressInfo file_info = init_compress_info();
    int error = 0;
    for(int i=1;i<argc;i++){
        resetCompressionInfo(&file_info);

        int error_arrived = decompress_handler(argv[i]);
        if(error_arrived) error = error_handler(error_arrived,i);

        if(error) break;
    }
    return 0;
}