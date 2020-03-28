//
//  a2_insertion.c
//  NearlyOptimalSearchTree
//
//  Created by Букшев Иван Евгеньевич on 25/03/2020.
//  Copyright © 2020 TA. All rights reserved.
//

#include "a2_insertion.h"
#include <stdlib.h>

/// Private: Определить индекс элемента, который будет корнем поддерева.
int subtree_root_index(tree_vertex const *const, int const, int const);

tree *a2_insertion(tree_vertex const *const vertexes, int const left, int const right) {
    if (right < left) {
        return NULL;
    }

    int const index = subtree_root_index(vertexes, left, right);

    tree *const root = (tree *const)malloc(sizeof(tree) * 2);

    root->vertex = vertexes[index];

    root->left = a2_insertion(vertexes, left, index - 1);
    root->right = a2_insertion(vertexes, index + 1, right);
    
    root->height = 1;
    calculate_and_set_tree_height(root);

    return root;
}

int subtree_root_index(tree_vertex const *const vertexes, int const left, int const right) {
    if (right <= left) {
        return left;
    }

    double weight = 0.0;
    int sum = 0;

    for (int i = left; i <= right; i++) {
        weight += vertexes[i].weight;
    }

    for (int i = left; i <= (right - 1); i++) {
        if ((sum < weight / 2) && ((weight / 2) < sum + vertexes[i].weight)) {
            return i;
            break;
        }
        sum = sum + vertexes[i].weight;
    }

    return right;
}
