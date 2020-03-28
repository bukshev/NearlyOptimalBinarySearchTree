//
//  a1_insertion.c
//  NearlyOptimalSearchTree
//
//  Created by Букшев Иван Евгеньевич on 25/03/2020.
//  Copyright © 2020 TA. All rights reserved.
//

#include "a1_insertion.h"
#include <stdlib.h>

/// Вставка вершины в дерево.
void insert_tree_vertex(tree **const, tree_vertex const);

void a1_insertion(tree **const root, tree_vertex *const vertexes, int const vertexes_count) {
    for (int i = 0; i < vertexes_count; i++) {
        int max_weight = 0;
        int max_weight_vertex_index = 0;
        
        for (int j = 0; j < vertexes_count; j++) {
            if ((max_weight < vertexes[j].weight) && (false == vertexes[j].is_used)) {
                max_weight = vertexes[j].weight;
                max_weight_vertex_index = j;
            }
        }

        vertexes[max_weight_vertex_index].is_used = true;
        insert_tree_vertex(root, vertexes[max_weight_vertex_index]);
    }
}

void insert_tree_vertex(tree **const root, tree_vertex const vertex) {
    if (NULL == *root) {
        *root = (tree *const)malloc(sizeof(tree));
        (*root)->vertex = vertex;
        (*root)->height = 1;
        (*root)->left = (*root)->right = NULL;
    } else {
        if (vertex.value < (*root)->vertex.value) {
            insert_tree_vertex(&(*root)->left, vertex);
        } else {
            insert_tree_vertex(&(*root)->right, vertex);
        }
    }
    calculate_and_set_tree_height(*root);
}
