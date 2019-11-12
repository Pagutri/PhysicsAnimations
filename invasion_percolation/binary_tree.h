#ifndef __y476_BINARYTREE_H
#define __y476_BINARYTREE_H

struct binary_tree
{
int random_number;
int index;
struct binary_tree *left;
struct binary_tree *right;
};


struct binary_tree *allocate_and_initialize_bintree\
                   (struct binary_tree **bintree);

int extend_bintree(struct binary_tree *bintree, int random_number, int index);

struct binary_tree *bintree_maxrandom_number_node(struct binary_tree *bintree);

struct binary_tree *bintree_minrandom_number_node(struct binary_tree *bintree);

void empty_bintree(struct binary_tree *bintree);

int remove_node_from_bintree(struct binary_tree *bintree, int random_number,\
                                            int index);

struct binary_tree *search_random_number_in_bintree(struct binary_tree *bintree,\
                                              int random_number);


#endif
