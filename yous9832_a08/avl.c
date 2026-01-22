/*
------------------------------------------
Project: a8q1
File: avl.c
Author: Antoine Youssef
Date: 2025-03-14
------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"


typedef struct record {
  char name[20];
  float score;
} RECORD;

typedef struct avlnode AVLNODE;

struct avlnode {
  RECORD data;
  int height;
  AVLNODE *left;
  AVLNODE *right;
};

/* Insert a node of given record data into AVL tree.
 *
 * @param rootp - pointer of pointer to tree root.
 * @param data  - record data for the new node.
 */
void avl_insert(AVLNODE **rootp, RECORD data){
     if (*rootp == NULL) {
    *rootp = avl_node(data);
  } else {
    if (strcmp(data.name, (*rootp)->data.name) < 0) {
      avl_insert(&(*rootp)->left, data);
    } else if (strcmp(data.name, (*rootp)->data.name) > 0) {
      avl_insert(&(*rootp)->right, data);
    }
  }
  (*rootp)->height = max(height((*rootp)->left), height((*rootp)->right)) + 1;
  int balance = balance_factor(*rootp);

  if (balance > 1 && strcmp(data.name, (*rootp)->left->data.name) < 0) {
    *rootp = rotate_right(*rootp);
  }
  else if (balance < -1 && strcmp(data.name, (*rootp)->right->data.name) > 0) {
    *rootp = rotate_left(*rootp);
  }
  else if (balance > 1 && strcmp(data.name, (*rootp)->left->data.name) > 0) {
    (*rootp)->left = rotate_left((*rootp)->left);
    *rootp = rotate_right(*rootp);
  }
  else if (balance < -1 && strcmp(data.name, (*rootp)->right->data.name) < 0) {
    (*rootp)->right = rotate_right((*rootp)->right);
    *rootp = rotate_left(*rootp);
  }
}

/* Delete a node of data.name matched with given key from AVL tree.
 *
 * @param rootp - pointer of pointer to tree root.
 * @param key -   key to match with data.name for deletion.
 */
void avl_delete(AVLNODE **rootp, char *name) {
  AVLNODE *root = *rootp;
  AVLNODE *np;

  if (root == NULL) return;

  if (strcmp(name, root->data.name) == 0) {
    if (root->left == NULL && root->right == NULL) {
      free(root);
      *rootp = NULL;
    } else if (root->left != NULL && root->right == NULL) {
      np = root->left;
      free(root);
      *rootp = np;
    } else if (root->left == NULL && root->right != NULL) {
      np = root->right;
      free(root);
      *rootp = np;
    } else if (root->left != NULL && root->right != NULL) {
      np = extract_smallest_node(&root->right);
      np->left = root->left;
      np->right = root->right;
      free(root);
      *rootp = np;
    }
  } else {
    if (strcmp(name, root->data.name) < 0) {
      avl_delete(&root->left, name);
    } else {
      avl_delete(&root->right, name);
    }
  }
  if (*rootp == NULL) return;
  root = *rootp;
  root->height = max(height(root->left), height(root->right)) + 1;
  int balance = balance_factor(root);
  if (balance > 1 && balance_factor(root->left) >= 0) {
    *rootp = rotate_right(root);
  }
  else if (balance < -1 && balance_factor(root->right) <= 0) {
    *rootp = rotate_left(root);
  }
  else if (balance > 1 && balance_factor(root->left) < 0) {
    root->left = rotate_left(root->left);
    *rootp = rotate_right(root);
  }
  else if (balance < -1 && balance_factor(root->right) > 0) {
    root->right = rotate_right(root->right);
    *rootp = rotate_left(root);
  }
}


/* Search AVL tree by key of the name field
 * @param root - pointer to tree root.
 * @param key - key to match with data.name for search
 * @return - node pointer if found, otherwise NULL
 */
AVLNODE *avl_search(AVLNODE *root, char *key){
    if (root==NULL || strcmp(root->data.name, key)==0){
        return root;
    }
    if (strcmp(root->data.name, key) < 0){
        return avl_search(root->right, key);
    } else {
        return avl_search(root->left, key);}
    }
/* This function clean AVL tree.
 * @param rootp - pointer of pointer of tree root.
 */
void avl_clean(AVLNODE **rootp) {
  AVLNODE *root = *rootp;
  if (root) {
    if (root->left)
      avl_clean(&root->left);
    if (root->right)
      avl_clean(&root->right);
    free(root);
  }
  *rootp = NULL;
}

/* Get the height of AVL tree
 * @param np - pointer to the root of tree
 * @return - the the height value at root.
 */
int height(AVLNODE *root){
    if (root == NULL){
        return 0;
    }
    return root->height;
}


/* Return the balance factor at the given node
 * @param np - pointer to the node of tree
 * @return - the balance factor a the node
 */
int balance_factor(AVLNODE *np){
    if (np == NULL){
        return 0;
    }
    return height(np->left) - height(np->right);
}

/* This function does the left rotation at a given node
 * @param np - pointer to the rotation node.
 * @return - the pointer to the replaced node.
 */
AVLNODE *rotate_left(AVLNODE *np) {
  AVLNODE *new_root = np->right;
  AVLNODE *temp = new_root->left;
  new_root->left = np;
  np->right = temp;
  np->height = max(height(np->left), height(np->right)) + 1;
  new_root->height = max(height(new_root->left), height(new_root->right)) + 1;

  return new_root;
}

/* This function does the right rotation at a given node
 * @param np - pointer to the rotation node.
 * @return - the pointer to the replaced node.
 */
AVLNODE *rotate_right(AVLNODE *root) {
  AVLNODE *new_root = root->left;
  AVLNODE *temp = new_root->right;
  new_root->right = root;
  root->left = temp;
  root->height = max(height(root->left), height(root->right)) + 1;
  new_root->height = max(height(new_root->left), height(new_root->right)) + 1;
  return new_root;
}