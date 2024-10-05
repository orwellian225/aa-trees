#pragma once

#include <stddef.h>
#include <stdint.h>

typedef struct BSTNode BSTNode;
struct BSTNode {
    int32_t key;
    BSTNode *parent;
    BSTNode *left;
    BSTNode *right;
    size_t size;
};

typedef struct {
    BSTNode *root;
} BSTree;


BSTNode *new_node(int32_t value);
void print_node(BSTNode *node, char *name);

void insert_node(BSTree *tree, BSTNode *node);

BSTNode *subtree_minimum(BSTNode *node);
void node_transplant(BSTree *tree, BSTNode *u, BSTNode *v);
void delete_node(BSTree *tree, BSTNode *node);

size_t measure_tree_height(BSTree *tree);
size_t measure_subtree_height(BSTNode *node);

void tree_walk_inorder(BSTree *tree);
void tree_walk_inorder_atnode(BSTNode *node);

void tree_walk_inorder_size(BSTree *tree);
void tree_walk_inorder_size_atnode(BSTNode *node);

void tree_walk_preorder(BSTree *tree);
void tree_walk_preorder_atnode(BSTNode *node);
