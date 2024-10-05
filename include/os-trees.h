#pragma once

#include <stddef.h>
#include <stdint.h>

typedef struct OSNode OSNode;
struct OSNode {
    int32_t key;
    OSNode *parent;
    OSNode *left;
    OSNode *right;
    size_t size;
};

typedef struct {
    OSNode *root;
} OSTree;

OSNode *new_osnode(int32_t value);
void print_osnode(OSNode *node, char *name);

void insert_osnode(OSTree *tree, OSNode *node);

OSNode *ossubtree_minimum(OSNode *node);
void osnode_transplant(OSTree *tree, OSNode *u, OSNode *v);
void delete_osnode(OSTree *tree, OSNode *node);

size_t measure_ostree_height(OSTree *tree);
size_t measure_ossubtree_height(OSNode *node);

void ostree_walk_inorder(OSTree *tree);
void ostree_walk_inorder_atnode(OSNode *node);

void ostree_walk_inorder_size(OSTree *tree);
void ostree_walk_inorder_size_atnode(OSNode *node);

void ostree_walk_preorder(OSTree *tree);
void ostree_walk_preorder_atnode(OSNode *node);

// Indexes from one so i'm going to fudge it in the initial call
OSNode *ostree_select(OSTree *tree, size_t search_rank);
OSNode *ostree_select_atnode(OSNode *node, size_t search_rank);

size_t ostree_rank(OSTree *tree, OSNode *node);
