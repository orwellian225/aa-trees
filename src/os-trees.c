#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "os-trees.h"

OSNode *new_osnode(int32_t value) {
    OSNode *node = (OSNode*) malloc(sizeof(OSNode));
    node->key = value;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    node->size = 1;

    return node;
}

void insert_osnode(OSTree *tree, OSNode *node) {
    OSNode *possible_parent = NULL;
    OSNode *position = tree->root;
    while (position != NULL) {
        position->size += 1;
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

void print_osnode(OSNode *node, char *name) {
    printf("%s Node: %p\n", name, node);
    printf("%s Node key: %d\n", name, node->key);
    printf("%s Node size: %ld\n", name, node->size);
    printf("%s Left Node: %p\n", name, node->left);
    printf("%s Right Node: %p\n", name, node->right);
    printf("%s Node Parent: %p\n", name, node->parent);
}

size_t measure_ostree_height(OSTree *tree) { return measure_ossubtree_height(tree->root) - 1; }
size_t measure_ossubtree_height(OSNode *node) {
    if (node == NULL)
        return 0;

    size_t left_height = measure_ossubtree_height(node->left) + 1;
    size_t right_height = measure_ossubtree_height(node->right) + 1;

    if (left_height < right_height)
        return right_height;
    else
        return left_height;
}

OSNode *ossubtree_minimum(OSNode *node) {
    OSNode *current = node;
    while (current->left != NULL)
        current = current->left;

    return current;
}

void osnode_transplant(OSTree *tree, OSNode *u, OSNode *v) {
    if (u->parent == NULL)
        tree->root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if (v != NULL)
        v->parent = u->parent;

}

void delete_osnode(OSTree *tree, OSNode *node) {
    if (node->left == NULL)
        osnode_transplant(tree, node, node->right);
    else if (node->right == NULL)
        osnode_transplant(tree, node, node->left);
    else {
        OSNode *minimum_node = ossubtree_minimum(node->right);

        if (minimum_node->parent != node) {
            minimum_node->size = node->right->size;
            node->right->size -= 1;

            osnode_transplant(tree, minimum_node, minimum_node->right);
            minimum_node->right = node->right;
            minimum_node->right->parent = minimum_node;

        }

        minimum_node->size += node->left->size;
        osnode_transplant(tree, node, minimum_node);
        minimum_node->left = node->left;
        minimum_node->left->parent = minimum_node;
    }

    // Updating size
    OSNode *current = node->parent;
    while(current != NULL) {
        current->size--;
        current = current->parent;
    }
}

void ostree_walk_inorder(OSTree *tree) {
    ostree_walk_inorder_atnode(tree->root);
    printf("\n");
}

void ostree_walk_inorder_atnode(OSNode *node) {
    if (node != NULL) {
        ostree_walk_inorder_atnode(node->left);
        printf("%d, ", node->key);
        ostree_walk_inorder_atnode(node->right);
    }
}

void ostree_walk_inorder_size(OSTree *tree) {
    ostree_walk_inorder_size_atnode(tree->root);
    printf("\n");
}

void ostree_walk_inorder_size_atnode(OSNode *node) {
    if (node != NULL) {
        ostree_walk_inorder_size_atnode(node->left);
        printf("%d(%ld), ", node->key, node->size);
        ostree_walk_inorder_size_atnode(node->right);
    }
}

void ostree_walk_preorder(OSTree *tree) {
    ostree_walk_preorder_atnode(tree->root);
    printf("\n");
}

void ostree_walk_preorder_atnode(OSNode *node) {
    if (node != NULL) {
        printf("%d, ", node->key);
        ostree_walk_preorder_atnode(node->left);
        ostree_walk_preorder_atnode(node->right);
    }
}

OSNode *ostree_select(OSTree *tree, size_t search_rank) { return ostree_select_atnode(tree->root, search_rank + 1); }
OSNode *ostree_select_atnode(OSNode *node, size_t search_rank) {
    size_t rank;
    if (node->left != NULL)
       rank = node->left->size + 1;
    else
        rank = 1;
    
    if (rank == search_rank)
        return node;

    if (rank > search_rank)
        return ostree_select_atnode(node->left, search_rank);

    return ostree_select_atnode(node->right, search_rank - rank);
}

size_t ostree_rank(OSTree *tree, OSNode *node) {
    size_t rank;    
    if (node->left != NULL)
        rank = node->left->size + 1;
    else
        rank = 1;

    OSNode *current_node = node;
    while (current_node != tree->root) {
        if (current_node == current_node->parent->right) { 
            if (current_node->parent->left != NULL)
                    rank += current_node->parent->left->size + 1;
            else
                rank += 1;
        }

        current_node = current_node->parent;
    }

    return rank - 1;
}
