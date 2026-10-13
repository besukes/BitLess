/* This module needs to compress the files , after the algorithm , but also leave the important
details about the compresssion so it can be decompressed after when , and if , needed.
*/
#include "sf_compressor.h"


/* Recursively applies Shannon-Fano's compression algorithm to turn the symbol into a sequence of bits*/
static int sfcompress(float * prob , NewSymbols * new_symb, int ns , float set_half_prob){
    //We reached the final depth of Shannon-Fano's Algorithm
    if(ns <= 1) return 1;

    float acc_prob = 0.0f;
    int n_left_tree = 0;

    int i;
    for(i=0;i < ns - 1; i++){
        acc_prob+=prob[i];
        n_left_tree ++;
        if(acc_prob >= set_half_prob) break;
    }
    if(fabsf(set_half_prob - acc_prob-prob[i]) < fabsf(set_half_prob - acc_prob)){
        acc_prob = acc_prob - prob[i];
        n_left_tree--; //Need to check if this works
    }

    float right_node_prob = 2*set_half_prob - acc_prob;

    for(int j=0 ; j < n_left_tree ; j++){
        new_symb[j].new_code = (new_symb[j].new_code << 1);
        new_symb[j].length++;
    }
    for(int u = n_left_tree ; u < ns ; u++){
        new_symb[u].new_code = (new_symb[u].new_code << 1) | 1ULL;
        new_symb[u].length++;
    }

    sfcompress(prob,new_symb,n_left_tree,acc_prob/2);
    sfcompress(prob+n_left_tree,new_symb+n_left_tree,ns-n_left_tree,right_node_prob/2);

    return 0;
}



/* Checks if the probability distribution has maximum entropy , because if it does then the file cannot be compressed*/
static int max_entropy(float * prob , int ns){
    if(ns > 0){ //Checks if theres atleast one symbol
        float prob_0 = prob[0];
        for(int i=1;i<ns;i++){
            if(prob[i] != prob_0) return 0; //If theres a symbol with a different probability then we can compress
        }
    }
    return 1;
}



/*  This function compresses the file using the Shannon-Fano algorithm and then writes out a file with the compressed data 
and also the necessary information for decompression.
    Returns 1 if sucess , e.g. the file is compressable , and 0 if not.*/
int compressFile(CompressInfo * file_info){
    DecrescentSortByP(file_info->symbols,file_info->probabilities,file_info->n_symbols);

    //Just for debugging
    if(IS_DEBUGGING_PARSED_S) debug_parsed_symbols(file_info);
    if(IS_DEBUGGING_PARSED_P) debug_parsed_probabilities(file_info);

    if(max_entropy(file_info->probabilities,file_info->n_symbols)) return 0;
    sfcompress(file_info->probabilities,file_info->newcode_arr,file_info->n_symbols,0.5f);

    //Just for debugging
    if(IS_DEBUGGING_NS) debug_NS_value(file_info);

    writeOutCompressedFile(file_info);
    return 1;
}