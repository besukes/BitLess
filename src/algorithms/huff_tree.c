#include "huff_tree.h"
/*
    Module that contains Huffman's data compression algorithm.
    This algorithm works by , given a crescently ordered list of each symbols probability , creates N leaf nodes ,
with N being the amount of symbols.
    The leaf nodes now get called child nodes and then the algorithm turns both of the less frequent nodes in
this set into just 1 and sorting the new set , creating a set with N-1 elements.
    This same procedure loops until we have only 1 NODE , which links to every other node through a tree.
    We can then travess the tree on it's left and right , and to each left subset we add a 1 to the path ,
and 0 to the right , increasing the depth of our recursive call function.
    When we reach a root , i.e both left and right nodes of a node are NULL , we know we reached a leaf node ,
and therefore we can assign that symbols code as the path it took from the root to that same NODE , and its code
length the function's recursive depth.

*/

/*  Removes the leaves[0] and leaves[1] from the array , substituing by the father node , and then sorting the entire array so we are left with
an array that has each element sorted by its frequency , crescently*/
static void SortChildNodes(Node * child[] , int N , Node * father , Node ** left , Node ** right){
    child[0] = father;
    for(int i=1;i<N-1;i++) child[i] = child[i+1]; //These 2 lines substitutes indexes 0 and 1 for the father

    N--; //Reduces the size , as we decreased 1 element in leaves
    // If we remove indx 0 and 1 and we are left with only 1 element , its the father
    // Therefore we should return
    if(N <= 1){
        *left = father;
        *right = NULL;
        return;
    }

    //Selection sort
    for(int i = 0; i < N - 1; i++){
        int min_idx = i;
        for(int j = i + 1; j < N; j++){
            if(child[j]->frequency < child[min_idx]->frequency){
                min_idx = j;
            }
        }
        if(min_idx != i){
            // Swap Nodes
            Node* temp = child[i];
            child[i] = child[min_idx];
            child[min_idx] = temp;
        }
    }
    // We know nchildren is greater than 1 , therefore it is memory safe to do this
    *left = child[0];
    *right = child[1];
}


/*  This function builds the tree based on the probabilities (crescently-ordered) of each symbol appearing on the file
    This function needs to be called with a copy of the "Probabilities Array" because it will change it.
    Because it always sorts before calling recursively , it assumes the indexes most to the left are the combination that brings less value.
*/
Node * build_tree(float * probabilities , int limArr , int totalsymb){
    if(limArr <= 1) return NULL; //for satefy measures , i.e if the starting array has only 1 element

    Node * child_nodes[limArr];
    for(int i=0;i<limArr;i++){ //Builds the leaf nodes of every symbol
        child_nodes[i] = malloc(sizeof(Node));
        child_nodes[i]->frequency = (int)(probabilities[i]*totalsymb);
        child_nodes[i]->indx = i; //This is the same index for the ULL newSymbols list , so this works out
        child_nodes[i]->left = NULL;
        child_nodes[i]->right = NULL;
    }

    // We know limArr > 1 , so we can use indexes 0 and 1
    Node * left_node = child_nodes[0] , 
         * right_node = child_nodes[1];
    Node * father = NULL;

    while(limArr > 1){
        //The new father node is consisted by the current left node frequency + the right_node frequency 
        father = malloc(sizeof(Node)); 
        father->frequency = left_node->frequency + right_node->frequency;
        father->indx = (-1);
        father->left = left_node;
        father->right = right_node;

        //It assumes the currently left_node and right_node are the indexes 0 and 1 of leaf_nodes , as it is always sorted
        SortChildNodes(child_nodes,limArr,father,&left_node,&right_node); //It assumes the currently left_node and right_node

        limArr--;
    }
    return (father);
}


/*Deconstructs the huffman tree and when it reaches the leaf nodes , gives each symbol its new format.*/
void deconstruct_tree(NewSymbols * new_symb , ULL path , int depth , Node * root){
    if(root!= NULL){
        if(root->left == NULL && root->right == NULL){
            new_symb[root->indx].new_code = path;
            new_symb[root->indx].length = depth;
        }
        else{
            ULL left_path = (path<<1) | 0 , 
                right_path = (path<<1) | 1;
            deconstruct_tree(new_symb,left_path,depth+1,root->left);
            deconstruct_tree(new_symb,right_path,depth+1,root->right);
        }
    }
}