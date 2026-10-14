#include "src/includes/types.h"


Node * build_tree(float * probabilities , int limArr , int totalsymb);
void deconstruct_tree(NewSymbols * new_symb , ULL path , int depth , Node * root);