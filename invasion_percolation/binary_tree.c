/*
 * The binary tree which is implemented here will 
 * always end with 'end cap' nodes on all of its leaves.
 * An end cap has 'random_number' = 0 and 'left' = 'right' = NULL.
 * The 0 'random_number' of an end cap is not counted as
 * a random_number of the binary tree.
 *
 */
#include "libraries.h"


struct binary_tree *allocate_and_initialize_bintree\
                   (struct binary_tree **bintree)
{
*bintree = (struct binary_tree *)malloc(sizeof(struct binary_tree));
if(NULL == *bintree)
  {
  printf("\n\nAllocation error in function"\
         " 'allocate_and_initialize_bintree()'\n\n");
  exit(0);
  }

(*bintree)->random_number = 0;  /* This is equivalent to (*(*bintree)).random_number */
(*bintree)->left  = NULL;
(*bintree)->right = NULL;
return(*bintree);
}



int extend_bintree(struct binary_tree *bintree, int random_number, int index)
{
/* Reaching a tree leaf and putting the random_number there: */
if((NULL == bintree->left) && (NULL == bintree->right))
  {
  bintree->left  = (struct binary_tree *)malloc(sizeof(struct binary_tree));
  bintree->right = (struct binary_tree *)malloc(sizeof(struct binary_tree));
  if((NULL == bintree->left) || (NULL == bintree->right))
    {
    printf("\n\nAllocation error in function"\
           " 'extend_bintree()'\n\n");
    exit(0);
    }
  bintree->random_number = random_number;
  bintree->index = index;

  bintree->left->random_number = 0;
  bintree->left->left = NULL;
  bintree->left->right = NULL;

  bintree->right->random_number = 0;
  bintree->right->left = NULL;
  bintree->right->right = NULL;
  return(random_number);
  }

/* Going to the left branch: */
if(random_number < bintree->random_number)
  {
  return(extend_bintree(bintree->left, random_number, index));
  }

/* Going to the right branch: */
return(extend_bintree(bintree->right, random_number, index));
}


struct binary_tree *bintree_maxrandom_number_node(struct binary_tree *bintree)
{
/*
 * Returns a pointer to the node with the biggest random_number
 * in 'bintree', or NULL if 'bintree' is an empty tree,
 * or NULL if 'bintree' is NULL.
 *
 */
if(NULL == bintree)
  {
  return(NULL);
  }
if((NULL == bintree->left) && (NULL == bintree->right))
  {
  return(NULL);
  }
if(NULL == bintree->left->left)
  {
  return(bintree);
  }
return(bintree_maxrandom_number_node(bintree->left));
}


struct binary_tree *bintree_minrandom_number_node(struct binary_tree *bintree)
{
/*
 * Returns a pointer to the node with the smallest random_number
 * in 'bintree', or NULL if 'bintree' is an empty tree,
 * or NULL if 'bintree' is NULL.
 *
 */
if(NULL == bintree)
  {
  return(NULL);
  }
if((NULL == bintree->left) && (NULL == bintree->right))
  {
  return(NULL);
  }
if(NULL == bintree->left->left)
  {
  return(bintree);
  }
return(bintree_minrandom_number_node(bintree->left));
}



void empty_bintree(struct binary_tree *bintree)
{
while((NULL != bintree->left) && (NULL != bintree->right))
  {
  remove_node_from_bintree(bintree, bintree->random_number, bintree->index);
  }
}



int remove_node_from_bintree(struct binary_tree *bintree, int random_number, int index)
{
/*
 * Removes the first (that is: upmost, closest to the tree trunk)
 * node with random_number 'random_number' from a given binary tree.
 * returns 0 if 'random_number' was not found in the tree,
 * or 1 upon success.
 *
 */
struct binary_tree *node_to_remove;
struct binary_tree *tmp_new_leftbranch;
struct binary_tree *tmp_new_rightbranch;
struct binary_tree *tmp_old_rightbranch;
struct binary_tree *maxend_of_new_node;
int tmp_new_random_number;
int tmp_new_index;

node_to_remove = search_random_number_in_bintree(bintree, random_number);
if(NULL == node_to_remove)
  {
  return(0);
  }

tmp_new_leftbranch  = node_to_remove->left->left;
tmp_new_rightbranch = node_to_remove->left->right;
tmp_new_random_number = node_to_remove->left->random_number;
tmp_new_index = node_to_remove->left->index;

tmp_old_rightbranch = node_to_remove->right;

free(node_to_remove->left);

node_to_remove->random_number = tmp_new_random_number;
node_to_remove->index = tmp_new_index;
node_to_remove->left  = tmp_new_leftbranch;
node_to_remove->right = tmp_new_rightbranch;

/*
 * Descent to the rightmost end node of tmp_new_rightbranch,
 * and append the 'tmp_old_rightbranch' pointer to it:
 *
 */
maxend_of_new_node = bintree_maxrandom_number_node(node_to_remove);
if(NULL != maxend_of_new_node)
  {
  free(maxend_of_new_node->right);
  maxend_of_new_node->right = tmp_old_rightbranch;
  }
/* in following 'else' case, 'node_to_remove' is an end cap [0] 
 *                                                          | |    
 *                                                       NULL  NULL   
 */
else
  {
  tmp_new_leftbranch = tmp_old_rightbranch->left;
  tmp_new_rightbranch = tmp_old_rightbranch->right;
  tmp_new_random_number = tmp_old_rightbranch->random_number;
  tmp_new_index = tmp_old_rightbranch->index;

  free(tmp_old_rightbranch);

  node_to_remove->random_number = tmp_new_random_number;
  node_to_remove->index = tmp_new_index;
  node_to_remove->left  = tmp_new_leftbranch;
  node_to_remove->right = tmp_new_rightbranch;  
  }

return(1);
}



struct binary_tree *search_random_number_in_bintree(struct binary_tree *bintree,\
                                              int random_number)
{
/* 
 * Returns a pointer to the first (that is: upmost, closest to the tree trunk)
 * node with random_number 'random_number' or NULL if random_number is not present in the tree.
 *
 */
if((NULL == bintree->left) && (NULL == bintree->right))
  {
  return(NULL);
  }

if(bintree->random_number == random_number)
  {
  return(bintree);
  }

if(random_number < bintree->random_number)
  {
  return(search_random_number_in_bintree(bintree->left, random_number));
  }
return(search_random_number_in_bintree(bintree->right, random_number));
}
