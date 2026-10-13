#include "init_clean.h"

/* Initializes the compression information structure */
CompressInfo init_compress_info(void){
    CompressInfo c;
    c.file = NULL;
    c.n_symbols = 0;
    c.is_open_file = 0;
    c.total_symbols = 0;
    c.newcode_arr= NULL;
    c.probabilities = NULL;
    c.symbols = NULL;
    c.file_path = NULL;
    c.number_zeros = 0;
    return c;
}

/* Frees the memory used for the compression*/
void free_memory(CompressInfo * c){
    free(c->symbols);
    free(c->probabilities);
    free(c->newcode_arr);
    if(c->is_open_file) fclose(c->file);
}


void resetCompressionInfo(CompressInfo * f){
    if(f->is_open_file) fclose(f->file);
    free(f->newcode_arr);
    free(f->symbols);
    free(f->probabilities);

    f->file = NULL;
    f->file_path = NULL;
    f->newcode_arr = NULL;
    f->symbols = NULL;
    f->probabilities = NULL;

    f->n_symbols = 0;
    f->is_open_file = 0;
    f->number_zeros = 0;
    f->total_symbols = 0;
}