#include <stdio.h>
#include <stdlib.h>

#include "os-trees.h"

int main() {
    OSTree *tree = (OSTree*)malloc(sizeof(OSTree));

    size_t num_nodes = 21;
    OSNode *values[] = { 
        new_osnode(0),  // 0
        new_osnode(-1), // 1
        new_osnode(7),  // 2
        new_osnode(-3), // 3
        new_osnode(4),  // 4
        new_osnode(11), // 5
        new_osnode(-2), // 6
        new_osnode(2),  // 7
        new_osnode(5),  // 8
        new_osnode(9),  // 9
        new_osnode(14), // 10
        new_osnode(1),  // 11
        new_osnode(3),  // 12
        new_osnode(6),  // 13
        new_osnode(8),  // 14
        new_osnode(10), // 15
        new_osnode(12), // 16
        new_osnode(16), // 17
        new_osnode(13), // 18
        new_osnode(15), // 19
        new_osnode(17), // 20
    };

    for (size_t i = 0; i < num_nodes; ++i)
        insert_osnode(tree, values[i]);

    printf("Original Tree\n");
    printf("-------------\n");
    ostree_walk_preorder(tree);
    ostree_walk_inorder_size(tree);
    printf("===============================================================\n\n");

    size_t delete_nodes[] = { 6, 3, 4, 5 };

    for (size_t i = 0; i < 4; ++i) {
        printf("Deleting %d\n", values[delete_nodes[i]]->key);
        printf("-----------\n");
        delete_osnode(tree, values[delete_nodes[i]]);
        ostree_walk_preorder(tree);
        ostree_walk_inorder_size(tree);
        printf("===============================================================\n\n");
    }

    char buffer[7];
    size_t i = 0;
    
    while(tree->root != NULL) {
        sprintf(buffer, "Root %ld", ++i);
        print_osnode(tree->root, buffer);
        delete_osnode(tree, tree->root);
    }

    /*printf("OS Select\n");*/
    /*for (size_t i = 0; i < num_nodes; ++i) {*/
    /*    OSNode *rank_node = ostree_select(tree, i);*/
        /*if (min_rank_node != NULL)*/
        /*    print_osnode(min_rank_node, "rank");*/
    /*    printf("Rank %ld | key %d\n", i, rank_node->key);*/
    /*}*/

    /*printf("OS Rank\n");*/
    /*for (size_t i = 0; i < num_nodes; ++i) {*/
    /*    size_t rank = ostree_rank(tree, values[i]);*/
    /*    printf("Key %d | rank %ld\n", values[i]->key, rank);*/
    /*}*/
}
