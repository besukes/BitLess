#include "sf.h"
/*  
    Module that contains Shannon Fano's compression algorithm.
    What this algorithm does is , after grabing each symbol and calculating its probability and
sorting them in an array in a decrescent order , it cuts the array in 2 subsets on each recursive call , 
according to the sum of the set total probability , which should be as close to half of the remaining probability
in a set.
    The "left subset" of the two is consisted of the most probable symbols , therefore each symbol 
will be atributed with a value of 0 on its respective code.
    The "right subset" will be given a code of 1.
    This recursiveness repeats until there's only 1 symbol in a set.
*/


/* Recursively applies Shannon-Fano's compression algorithm to turn the symbol into a sequence of bits*/
int sfcompress(float * prob , NewSymbols * new_symb, int ns , float set_half_prob){
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