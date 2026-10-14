/* This module needs to compress the files , after the algorithm , but also leave the important
details about the compresssion so it can be decompressed after when , and if , needed.
*/
#include "compressor.h"


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
    if(COMPRESSION_ALGORITHM == ShannonFano) 
        DecrescentSortByP(file_info->symbols,file_info->probabilities,file_info->n_symbols);
    else CrescentSortByP(file_info->symbols,file_info->probabilities,file_info->n_symbols);

    //Just for debugging
    if(IS_DEBUGGING_PARSED_S) debug_parsed_symbols(file_info);
    if(IS_DEBUGGING_PARSED_P) debug_parsed_probabilities(file_info);

    if(max_entropy(file_info->probabilities,file_info->n_symbols)) return 0;

    if(COMPRESSION_ALGORITHM == Huffman){
        Node * tree_root = build_tree(file_info->probabilities,file_info->n_symbols,file_info->total_symbols);
        deconstruct_tree(file_info->newcode_arr,0,0,tree_root);
    }
    else sfcompress(file_info->probabilities,file_info->newcode_arr,file_info->n_symbols,0.5f);

    //Just for debugging
    if(IS_DEBUGGING_NS) debug_NS_value(file_info);

    writeOutCompressedFile(file_info);
    return 1;
}