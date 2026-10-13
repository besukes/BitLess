#include "debug.h"



/*Debugs NEWSYMBOLS values calculated by sfcompressor*/
void debug_NS_value(CompressInfo* file_info){
    for(int i=0;i<file_info->n_symbols;i++){
        printf("[DEBUG NEWSYMBOL] new_symbol[%d] is %llu\n",i,file_info->newcode_arr[i].new_code);
    }
}

/*Debugs the parsed symbols found in the file read*/
void debug_parsed_symbols(CompressInfo* file_info){
    for(int i=0;i<file_info->n_symbols;i++){
        printf("[DEBUG] P_SYMBOL[%d] is %c\n",i,file_info->symbols[i]);
    }
}

/*Debugs the probabilites of each symbol appearing in the file*/
void debug_parsed_probabilities(CompressInfo* file_info){
    float total = 0;
    for(int i=0;i<file_info->n_symbols;i++){
        printf("[DEBUG] P_PROBABILITIES[%d] is %f\n",i,file_info->probabilities[i]);
        total+=file_info->probabilities[i];
    }
     printf("[DEBUG] probabilities sum is %f\n",total);
}
