#include "src/includes/types.h"


static void SortLeafNodes(Node * leaves[] , int nleaves , Node * father , Node ** left , Node ** right);
Node * build_tree(float * probabilities , int limArr , int totalsymb);