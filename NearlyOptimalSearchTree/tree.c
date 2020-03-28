//
//  tree.c
//  NearlyOptimalSearchTree
//
//  Created by Букшев Иван Евгеньевич on 25/03/2020.
//  Copyright © 2020 TA. All rights reserved.
//

#include "tree.h"

/// Private: Вычисление суммы длин путей от корня до каждой вершины.
int sum_of_all_path_lengths(tree const *const, int const);

void calculate_and_set_tree_height(tree *const root) {
	int const left_subtree_height = read_tree_height(root->left);
	int const right_subtree_height = read_tree_height(root->right);
	root->height = (left_subtree_height < right_subtree_height ? right_subtree_height : left_subtree_height) + 1;
}

int read_tree_height(tree const *const root) {
	if (NULL == root) {
		return 0;
	}
	return root->height;
}

int max_height(tree const *const root) {
	if (NULL == root) {
		return 0;
	}
	return 1 + (max_height(root->left) < max_height(root->right) ? max_height(root->right) : max_height(root->left));
}

double tree_average_height(tree const *const root) {
	if (NULL == root) {
		return 0.0;
	}
	return (double)sum_of_all_path_lengths(root, 1) / (double)tree_dimension(root);
}

int tree_dimension(tree const *const root) {
	if (NULL == root) {
		return 0;
	}
	return 1 + tree_dimension(root->left) + tree_dimension(root->right);
}

int tree_checksum(tree const *const root) {
	if (NULL == root) {
		return 0;
	}
	return root->vertex.value + tree_checksum(root->left) + tree_checksum(root->right);
}

void tree_traversal(tree const *const root) {
	if (NULL == root) {
		return;
	}

	tree_traversal(root->left);

	printf("\n%d", root->vertex.value);

	tree_traversal(root->right);
}

void calculate_weight_average_height(tree const *const root, int const tree_height, int *const hs, int *const ws) {
	if (NULL == root) {
		return;
	}

	calculate_weight_average_height(root->left, tree_height, hs, ws);

	*hs = *hs + (tree_height - root->height + 1) * root->vertex.weight;
	*ws = *ws + root->vertex.weight;

	calculate_weight_average_height(root->right, tree_height, hs, ws);
}

int sum_of_all_path_lengths(tree const *const root, int const temp) {
	if (NULL == root) {
		return 0;
	}
	return temp + sum_of_all_path_lengths(root->left, temp + 1) + sum_of_all_path_lengths(root->right, temp + 1);
}
