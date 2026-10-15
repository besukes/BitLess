#include "write_out.h"


/*Writes decompresssion info in the notation NEW_SYMBOL = OLD_SYMBOL in order to decompress after*/
static void writeDecompressionInfo(FILE * new_file , CompressInfo * file_info){
    fprintf(new_file,"%d\n",0);
    int size = file_info->n_symbols;
    for(int i=0;i<size;i++){
        fputc(file_info->symbols[i],new_file);
        fputc(file_info->newcode_arr[i].length,new_file);
    }
    fprintf(new_file,"\nend\n");
}


/*Writes out the bits of the new symbol to the buffer and print to the file when it reaches a size of 8 bits*/
static void write_out_compressed(BitWriter* bw , unsigned long long value , int n_bits){
    for(int i=n_bits - 1;i>=0;i--){ //Reads MSB first , left to right
        bw->buffer = (bw->buffer << 1) | ((value >> i) & 1ULL); //Grabs the current "i" bit
        bw->flush_bits++;
        if(bw->flush_bits == 8){
            fputc(bw->buffer,bw->file);
            bw->flush_bits = 0;
            bw->buffer = 0;
        }
    }
}

/*Flushes the last bits in the buffer when the file was completely read , to avoid leaving important info behind*/
static int flushout(BitWriter * bw){
    int ret = bw->flush_bits;
    if(bw->flush_bits > 0){
        bw->buffer <<= (8 - bw->flush_bits); 
        fputc(bw->buffer,bw->file);
        bw->flush_bits = 0;
        bw->buffer = 0;
    }
    return ret;
}

/*Good looking function that counts how many relevant bits a 64 bit number has*/
int count_bits(unsigned long long value){
    int counter=0;
    while((value>>counter)!=0) counter++;
    return counter;
}

/*Given an line from a life prints out the given new symbol generated that represents each character on it.*/
static void writeCompressedFileLine(char * line , CompressInfo * file_info , BitWriter * bw){
    //Just for safety purposes
    if(file_info->n_symbols == 0){
        printf("[ATTENTION] No symbols found in file\n");
        return;
    }

    int i=0;
    while(line[i]!='\0'){ //Loops through the entire line to map each character to its new code 
        int j=0;
        for(;j<file_info->n_symbols && line[i] != file_info->symbols[j];j++);
        if(j == file_info->n_symbols) printf("[ERROR] Error while finding symbol\n");

        unsigned long long temp = file_info->newcode_arr[j].new_code;
        if(temp == 0) file_info->number_zeros++; //Needs to be better handled
        write_out_compressed(bw,temp,file_info->newcode_arr[j].length);
        i++;
    }
}


/*Given a already parsed "f" file , checks if theres already a compressed file relative to f and , if not ,
compresses the file with some simple functions*/
void writeOutCompressedFile(CompressInfo * file_info){
    int length = strlent(file_info->file_path);
    char new_path[length + 8];

    if(COMPRESSION_ALGORITHM == ShannonFano)
        append_before_format(file_info->file_path,new_path,"_sf.zip");
    else append_before_format(file_info->file_path,new_path,"_hf.zip");

    FILE * new_file = fopen(new_path,"r");
    if(new_file!=NULL){
        fclose(new_file);
        printf("There's already a file named %s , therefore the program won't overwrite\n",new_path);
        return;
    }
    new_file = fopen(new_path,"w");

    writeDecompressionInfo(new_file,file_info);

    //This refers to the file that is being compressed
    fclose(file_info->file);//Assumes file exists
    file_info->file = fopen(file_info->file_path,"r"); //Opens it again to read the file one more time to print

    BitWriter bw;
    bw.file = new_file;
    bw.buffer = 0;
    bw.flush_bits = 0;

    char line[LINE_MAX];
    while(fgets(line,LINE_MAX,file_info->file)){
        writeCompressedFileLine(line,file_info,&bw);
    }
    int flushout_bits = flushout(&bw);

    //Updates to store the last relevant bits on the last byte of the file
    fseek(new_file,0,SEEK_SET);
    fprintf(new_file,"%d\n",flushout_bits);
    fseek(new_file,0,SEEK_END);

    fclose(new_file);
}