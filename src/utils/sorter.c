#include "src/includes/types.h"


/*Sorts Descrently by probability*/
void DecrescentSortByP(char *symbols, float *probability, int number_s){
    for(int i = 0; i < number_s - 1; i++){
        int max_idx = i;
        for(int j = i + 1; j < number_s; j++){
            if(probability[j] > probability[max_idx]){
                max_idx = j;
            }
        }
        if(max_idx != i){
            // Swap probabilities
            float f_temp = probability[i];
            probability[i] = probability[max_idx];
            probability[max_idx] = f_temp;

            // Swap symbols
            char c_temp = symbols[i];
            symbols[i] = symbols[max_idx];
            symbols[max_idx] = c_temp;
        }
    }
}


/*Sorts Descrently by probability, still need to change this*/
void CrescentSortByP(float *probability, int number_s){
    for(int i = 0; i < number_s - 1; i++){
        int min_idx = i;
        for(int j = i + 1; j < number_s; j++){
            if(probability[j] < probability[min_idx]){
                min_idx = j;
            }
        }
        if(min_idx != i){
            // Swap probabilities
            float f_temp = probability[i];
            probability[i] = probability[min_idx];
            probability[min_idx] = f_temp;
        }
    }
}