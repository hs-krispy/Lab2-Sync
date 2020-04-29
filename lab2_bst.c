/*
*	Operating System Lab
*	    Lab2 (Synchronization)
*	    Student id : 
*	    Student name : 
*
*   lab2_bst.c :
*       - thread-safe bst code.
*       - coarse-grained, fine-grained lock code
*
*   Implement thread-safe bst for coarse-grained version and fine-grained version.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <string.h>

#include "lab2_sync_types.h"

/*
 * TODO
 *  Implement funtction which traverse BST in in-order
 *  
 *  @param lab2_tree *tree  : bst to print in-order. 
 *  @return                 : status (success or fail)
 */
int lab2_node_print_inorder(lab2_tree *tree) {
    // You need to implement lab2_node_print_inorder function.
}

/*
 * TODO
 *  Implement function which creates struct lab2_tree
 *  ( refer to the ./include/lab2_sync_types.h for structure lab2_tree )
 * 
 *  @return                 : bst which you created in this function.
 */
lab2_tree *lab2_tree_create() {
    // You need to implement lab2_tree_create function.
}

/*
 * TODO
 *  Implement function which creates struct lab2_node
 *  ( refer to the ./include/lab2_sync_types.h for structure lab2_node )
 *
 *  @param int key          : bst node's key to creates
 *  @return                 : bst node which you created in this function.
 */
lab2_node * lab2_node_create(int key) {
    // You need to implement lab2_node_create function.
}

/* 
 * TODO
 *  Implement a function which insert nodes from the BST. 
 *  
 *  @param lab2_tree *tree      : bst which you need to insert new node.
 *  @param lab2_node *new_node  : bst node which you need to insert. 
 *  @return                 : satus (success or fail)
 */
int lab2_node_insert(lab2_tree *tree, lab2_node *new_node) {
    lab2_node *temp = tree -> root;
    if(temp == NULL) {
        tree -> root = new_node; // root가 NULL이면 새로운 노드를 root로 설정
        return SUCCESS;
    } else {
        while(1) {
            if(temp -> key < new_node -> key) { // 비교 노드의 키값보다 추가할 노드의 키값이 클 때
                if(!(temp -> right)) { // 비교노드의 오른쪽 자식이 NULL 일 때
                    temp -> right =  new_node;
                    break;
                }
                temp = temp -> right;
            } else if(temp -> key > new_node -> key) { // 비교 노드의 키값보다 추가할 노드의 키값이 작을 때
                if(!(temp -> left)) { // 비교노드의 왼쪽 자식이 NULL 일 때
                    temp -> left = new_node;
                    break;
                }
                temp = temp -> left;
            }
        }
    }
    return SUCCESS;
}

/* 
 * TODO
 *  Implement a function which insert nodes from the BST in fine-garined manner.
 *
 *  @param lab2_tree *tree      : bst which you need to insert new node in fine-grained manner.
 *  @param lab2_node *new_node  : bst node which you need to insert. 
 *  @return                     : status (success or fail)
 */
int lab2_node_insert_fg(lab2_tree *tree, lab2_node *new_node){
      // You need to implement lab2_node_insert_fg function.
}

/* 
 * TODO
 *  Implement a function which insert nodes from the BST in coarse-garined manner.
 *
 *  @param lab2_tree *tree      : bst which you need to insert new node in coarse-grained manner.
 *  @param lab2_node *new_node  : bst node which you need to insert. 
 *  @return                     : status (success or fail)
 */
int lab2_node_insert_cg(lab2_tree *tree, lab2_node *new_node){
    lab2_node *temp = tree -> root;
    if(temp == NULL) {
        tree -> root = new_node;
        return SUCCESS;
    } else {
        pthread_mutex_lock(&new_node->mutex); // lock 걸어줌
        while(1) {
            if(temp -> key < new_node -> key) {
                if(!(temp -> right)) {
                    temp -> right =  new_node;
                    break;
                }
                temp = temp -> right;
            } else if(temp -> key > new_node -> key) {
                if(!(temp -> left)) {
                    temp -> left = new_node;
                    break;
                }
                temp = temp -> left;
            }
        }
        pthread_mutex_unlock(&new_node->mutex); // lock 해제
    }
    return SUCCESS;
}

/* 
 * TODO
 *  Implement a function which remove nodes from the BST.
 *
 *  @param lab2_tree *tree  : bst tha you need to remove node from bst which contains key.
 *  @param int key          : key value that you want to delete. 
 *  @return                 : status (success or fail)
 */
int lab2_node_remove(lab2_tree *tree, int key) {
    lab2_node *temp = tree -> root;
    lab2_node *parent, *child = NULL;
    if(temp == NULL) {
        return SUCCESS;
    }
    while(temp -> key != key) {
        if(temp -> key < key) {
            parent = temp;
            temp = temp -> right;
        } else {
            parent = temp;
            temp = temp -> left;
        }
    }
    if(temp -> left == NULL && temp -> right == NULL) { // 아래에 자식 노드가 없을 경우
        if(parent -> left == temp) {
            parent -> left = NULL;
        }
        if(parent -> right == temp) {
            parent -> right == NULL;
        }
        lab2_node_delete(temp);
        return SUCCESS;
    }
    if(temp -> left == NULL || temp -> right == NULL) { // 아래에 1개의 자식 노드가 있을 경우
        if(temp -> left) {
            child = temp -> left;
        } else {
            child = temp -> right;
        }
        if(parent -> left == temp) {
            parent -> left = child;
        } else {
            parent -> right = child;
        }
        lab2_node_delete(temp);
        return SUCCESS;
    }
    if(temp -> left != NULL && temp -> right != NULL) { // 아래에 2개의 자식 노드가 있을 경우
        lab2_node *temp2 = temp -> right;
        while(temp2->left != NULL){
            parent = temp2;
            temp2 = temp2->left;
        }
        temp->key = temp2->key;
        if(temp2->right != NULL){
            parent->left = temp2->right;
        }
        lab2_node_delete(temp2);
        return SUCCESS;
    }
}

/* 
 * TODO
 *  Implement a function which remove nodes from the BST in fine-grained manner.
 *
 *  @param lab2_tree *tree  : bst tha you need to remove node in fine-grained manner from bst which contains key.
 *  @param int key          : key value that you want to delete. 
 *  @return                 : status (success or fail)
 */
int lab2_node_remove_fg(lab2_tree *tree, int key) {
    // You need to implement lab2_node_remove_fg function.
}


/* 
 * TODO
 *  Implement a function which remove nodes from the BST in coarse-grained manner.
 *
 *  @param lab2_tree *tree  : bst tha you need to remove node in coarse-grained manner from bst which contains key.
 *  @param int key          : key value that you want to delete. 
 *  @return                 : status (success or fail)
 */
int lab2_node_remove_cg(lab2_tree *tree, int key) {
    // You need to implement lab2_node_remove_cg function.
}


/*
 * TODO
 *  Implement function which delete struct lab2_tree
 *  ( refer to the ./include/lab2_sync_types.h for structure lab2_node )
 *
 *  @param lab2_tree *tree  : bst which you want to delete. 
 *  @return                 : status(success or fail)
 */
void lab2_tree_delete(lab2_tree *tree) { // 트리를 초기화
    lab2_node *temp = tree -> root;
    if(!temp) return;
    while(temp) {
        int key = temp -> key;
        lab2_node_remove(tree, key);
        temp = tree -> root;
    }
}

/*
 * TODO
 *  Implement function which delete struct lab2_node
 *  ( refer to the ./include/lab2_sync_types.h for structure lab2_node )
 *
 *  @param lab2_tree *tree  : bst node which you want to remove. 
 *  @return                 : status(success or fail)
 */
void lab2_node_delete(lab2_node *node) { // 삭제한 노드의 메모리 할당 제거
    free(node);
}

