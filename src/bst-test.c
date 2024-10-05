#include <stdio.h>
#include <stdlib.h>

#include "bs-trees.h"

int main() {
    BSTree *tree = (BSTree*)malloc(sizeof(BSTree));

    BSTNode *values[] = { 
        new_node(0),
        new_node(-2),
        new_node(-3),
        new_node(-1),
        new_node(3),
        new_node(2),
        new_node(5),
        new_node(1),
        new_node(4),
        new_node(6)
    };

    for (size_t i = 0; i < 10; ++i)
        insert_node(tree, values[i]);

    tree_walk_inorder(tree);

    size_t tree_height = measure_tree_height(tree);
    printf("Tree height: %ld\n", tree_height);

    for (size_t i = 0; i < 10; ++i)
        delete_node(tree, tree->root);

    tree_walk_inorder(tree);
}
