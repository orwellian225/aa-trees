#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "os-trees.h"

int main(int argc, char **argv) {
    size_t chosen_n = 10;
    if (argc == 2)
        chosen_n = atoll(argv[1]);

    size_t max_n = 200;
    if (chosen_n > max_n)
        chosen_n = max_n;

    OSTree *os_tree = (OSTree*)malloc(sizeof(OSTree));
    OSNode **os_nodes = (OSNode**)malloc(max_n * sizeof(OSNode*));

    int32_t keys[] = { 
        -387, -450, -166, -112, 407, 378, 39, 373, 345, 46, -352, -173, -495, 21, -298, 26, -124, 447, 166, -176, -18,
        -95, 40, -208, 135, -187, -289, -416, -157, 103, 481, -276, -109, 188, 394, 243, -221, -244, 75, 284, 457, 280,
        -159, 289, -463, 242, 304, 144, 410, 10, 290, -392, 315, -227, 494, 408, 458, 224, -148, -447, -14, 156, -192,
        -469, 189, 335, 177, -80, -144, 157, 437, 34, 444, 3, -319, -340, -200, -30, 139, -107, 185, -103, 196, -346,
        -193, 134, -51, -72, 31, 438, -92, -475, -13, 450, 365, -490, 226, -425, 25, 122, 153, 29, 19, 14, 418, 115,
        -367, -7, 395, -217, -143, 217, -303, -494, 385, -334, 165, -211, 414, -321, 324, -66, -294, 16, 176, -85, -76,
        274, 129, 254, 36, -108, 51, -388, -188, -403, -150, -474, 351, -266, 17, 460, -54, 422, -160, 102, 59, 213,
        247, -48, -81, -70, -53, 464, 208, 309, 95, -379, -99, -91, 198, -170, -451, 352, 108, 1, 63, 120, -389, -292,
        -428, -77, -38, -41, 58, -60, 416, 99, -34, -385, 402, 439, 291, -96, 249, -40, -3, 273, 223, -246, -68, 82,
        -74, -191, -93, 168, 132, 485, 264, -126 
    };

    for (size_t n = 0; n < chosen_n; n++) {
        os_nodes[n] = new_osnode(keys[n]);
    }

    for (size_t n = 0; n < chosen_n; n++)
        insert_osnode(os_tree, os_nodes[n]);


    printf("Inorder Walk: ");
    ostree_walk_inorder(os_tree);
    printf("Inorder Walk with Size key(size): ");
    ostree_walk_inorder_size(os_tree);
    printf("Preorder Walk: ");
    ostree_walk_preorder(os_tree);
    printf("========================================\n");
    OSNode *median_node = ostree_select(os_tree, chosen_n / 2);
    print_osnode(median_node, "Median");
    printf("Median Rank: %ld\n", ostree_rank(os_tree, median_node));


    printf("========================================\n");
    OSNode *first_quartile_node = ostree_select(os_tree, chosen_n / 4);
    print_osnode(first_quartile_node, "First Quartile");
    printf("First Quartile Rank: %ld\n", ostree_rank(os_tree, first_quartile_node));

    printf("========================================\n");
    OSNode *third_quartile_node = ostree_select(os_tree, 3 * chosen_n / 4);
    print_osnode(third_quartile_node, "Third Quartile");
    printf("Third Quartile Rank: %ld\n", ostree_rank(os_tree, third_quartile_node));

}
