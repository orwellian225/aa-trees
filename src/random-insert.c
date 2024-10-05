#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "bs-trees.h"
#include "os-trees.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Incorrect arguments\n");
        return -1;
    }
    size_t max_n = atoll(argv[1]);
    size_t range = atoll(argv[2]);

    int32_t min_key = -1 * range;
    int32_t max_key = range;

    BSTree *tree = (BSTree*)malloc(sizeof(BSTree));
    BSTNode **nodes = (BSTNode**)malloc(max_n * sizeof(BSTNode*));

    OSTree *os_tree = (OSTree*)malloc(sizeof(OSTree));
    OSNode **os_nodes = (OSNode**)malloc(max_n * sizeof(OSNode*));

    for (size_t n = 0; n < max_n; n++) {
        int32_t new_key = (rand() % (max_key - min_key + 1)) + min_key;
        nodes[n] = new_node(new_key);
        os_nodes[n] = new_osnode(new_key);
    }

    clock_t build_start_time, build_end_time;
    build_start_time = clock();
    for (size_t n = 0; n < max_n; n++)
        insert_node(tree, nodes[n]);
    build_end_time = clock();
    double build_duration = (double)(build_end_time - build_start_time) / CLOCKS_PER_SEC;

    clock_t os_build_start_time, os_build_end_time;
    os_build_start_time = clock();
    for (size_t n = 0; n < max_n; n++)
        insert_osnode(os_tree, os_nodes[n]);
    os_build_end_time = clock();
    double os_build_duration = (double)(os_build_end_time - os_build_start_time) / CLOCKS_PER_SEC;

    size_t tree_height = measure_tree_height(tree);
    size_t os_tree_height = measure_ostree_height(os_tree);

    clock_t destroy_start_time, destroy_end_time;
    destroy_start_time = clock();
    while(tree->root != NULL)
        delete_node(tree, tree->root);
    destroy_end_time = clock();
    double destroy_duration = (double)(destroy_end_time - destroy_start_time) / CLOCKS_PER_SEC;

    clock_t os_destroy_start_time, os_destroy_end_time;
    os_destroy_start_time = clock();
    while(os_tree->root != NULL)
        delete_osnode(os_tree, os_tree->root);
    os_destroy_end_time = clock();
    double os_destroy_duration = (double)(os_destroy_end_time - os_destroy_start_time) / CLOCKS_PER_SEC;

    printf("%ld,BST,%ld,%lf,%lf\n", max_n, tree_height, build_duration, destroy_duration);
    printf("%ld,OST,%ld,%lf,%lf\n", max_n, os_tree_height, os_build_duration, os_destroy_duration);
}
