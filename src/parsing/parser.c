#include "parser.h"

/* Passes the symbols of the file to an array of symbols */
static void assertSymbols(char * orig , int number_s , char * dest){
    for(int i = 0 ; i < number_s ; i++){
        *(dest + i) = *(orig + i);
    }
}

/*Calculates the probability of each symbol appearing on the file.*/
static void assertProbabilities(int * freq , int number_s , int total_number_s , float * dest){
    float total = (float)total_number_s;
    for(int i=0 ; i < number_s ; i++){
        dest[i] = (float)freq[i] / total;
    }
}



/*Translates what we have read from each line to actual meaningful information to latter use for 
compression.*/
static void info_parser(int symbols[MAX_SYMBOLS], CompressInfo * file_info){
    int number_symbols = 0;
    char file_symbols[256];
    int freq_symbols[256];
    for(int i = 0 ; i < MAX_SYMBOLS ; i++){
        if(symbols[i]){
            file_symbols[number_symbols] = (char)i;
            freq_symbols[number_symbols] = symbols[i];
            if(IS_DEBUGGING_PARSED_FREQ) printf("%d\n",symbols[i]);
            number_symbols++;
        }
    }

    file_info->n_symbols = number_symbols;
    file_info->symbols = malloc(sizeof(char)*number_symbols);
    file_info->probabilities = malloc(sizeof(float)*number_symbols);
    file_info->newcode_arr = calloc(number_symbols,sizeof(NewSymbols)*number_symbols);
    
    assertSymbols(file_symbols,number_symbols,file_info->symbols);
    assertProbabilities(freq_symbols,number_symbols,file_info->total_symbols,file_info->probabilities);

    if(IS_DEBUGGING_PARSED_S) debug_parsed_symbols(file_info);
    if(IS_DEBUGGING_PARSED_P) debug_parsed_probabilities(file_info);
}


/* Reads each individual file line incrementing symbols array on its respective index ,
 for each time an symbol is seen.*/
static void lineParser(char line[LINE_MAX] , int symbols[MAX_SYMBOLS] , int * total_symbols){
    for(int i=0;line[i] != '\0'; i++){
        unsigned char symb = (unsigned char)line[i];
        symbols[symb]++;
        (*total_symbols)++;
    }
}

/* Parses the file reading each symbol and its probability , returns 1 on SUCESS if path exists and 0 
on fail , aka the file path doesnt return any actual file.*/
int parseArguments(char * path , CompressInfo * file_info){
    FILE * file = fopen(path,"r");
    if(file == NULL) return 0;
    file_info->is_open_file = 1;
    file_info->file = file;
    file_info->file_path = path;

    int symbols[MAX_SYMBOLS] = {0};
    char line[LINE_MAX];

    while(fgets(line,LINE_MAX,file)){
        lineParser(line,symbols,&file_info->total_symbols);
    }
    info_parser(symbols,file_info);
    return 1;
}