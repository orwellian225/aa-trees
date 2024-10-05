#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "bs-trees.h"

BSTNode *new_node(int32_t value) {
    BSTNode *node = (BSTNode*) malloc(sizeof(BSTNode));
    node->key = value;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void insert_node(BSTree *tree, BSTNode *node) {
    BSTNode *possible_parent = NULL;
    BSTNode *position = tree->root;
    while (position != NULL) {
        possible_parent = position;
        if (node->key <= position->key)
            position = position->left;
        else
            position = position->right;
    }

    node->parent = possible_parent;
    if (possible_parent == NULL)
        tree->root = node;
    else if (node->key < possible_parent->key)
        possible_parent->left = node;
    else
        possible_parent->right = node;
}

void print_node(BSTNode *node, char *name) {
    printf("%s Node: %p\n", name, node);
    printf("%s Node key: %d\n", name, node->key);
    printf("%s Left Node: %p\n", name, node->left);
    printf("%s Right Node: %p\n", name, node->right);
    printf("%s Node Parent: %p\n", name, node->parent);
}

size_t measure_tree_height(BSTree *tree) { return measure_subtree_height(tree->root) - 1; }
size_t measure_subtree_height(BSTNode *node) {
    if (node == NULL)
        return 0;

    size_t left_height = measure_subtree_height(node->left) + 1;
    size_t right_height = measure_subtree_height(node->right) + 1;

    if (left_height < right_height)
        return right_height;
    else
        return left_height;
}

BSTNode *subtree_minimum(BSTNode *node) {
    BSTNode *current = node;
    while (current->left != NULL)
        current = current->left;

    return current;
}

void node_transplant(BSTree *tree, BSTNode *u, BSTNode *v) {
    if (u->parent == NULL)
        tree->root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if (v != NULL)
        v->parent = u->parent;

}

void delete_node(BSTree *tree, BSTNode *node) {
    if (node->left == NULL)
        node_transplant(tree, node, node->right);
    else if (node->right == NULL)
        node_transplant(tree, node, node->left);
    else {
        BSTNode *minimum_node = subtree_minimum(node->right);

        if (minimum_node->parent != node) {
            node_transplant(tree, minimum_node, minimum_node->right);
            minimum_node->right = node->right;
            minimum_node->right->parent = minimum_node;
        }

        node_transplant(tree, node, minimum_node);
        minimum_node->left = node->left;
        minimum_node->left->parent = minimum_node;
    }
}

void tree_walk_inorder(BSTree *tree) {
    tree_walk_inorder_atnode(tree->root);
    printf("\n");
}

void tree_walk_inorder_atnode(BSTNode *node) {
    if (node != NULL) {
        tree_walk_inorder_atnode(node->left);
        printf("%d, ", node->key);
        tree_walk_inorder_atnode(node->right);
    }
}

void tree_walk_preorder(BSTree *tree) {
    tree_walk_preorder_atnode(tree->root);
    printf("\n");
}

void tree_walk_preorder_atnode(BSTNode *node) {
    if (node != NULL) {
        printf("%d, ", node->key);
        tree_walk_preorder_atnode(node->left);
        tree_walk_preorder_atnode(node->right);
    }
}
