//
//  main.c
//  NearlyOptimalSearchTree
//
//  Created by Букшев Иван Евгеньевич on 25/03/2020.
//  Copyright © 2020 TA. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tree.h"

#include "a1_insertion.h"
#include "a2_insertion.h"

/// Количество вершин, из которых будет состоять дерево.
static size_t const VERTEXES_COUNT = 500;
/// Минимальный вес для вершины.
static int const MIN_WEIGHT = 0;
/// Максимальный вес для вершины.
static int const MAX_WEIGHT = 999;
/// Минимальное значение для вершины дерева.
static int const MIN_VALUE = 0;
/// Максимальное значение для вершины дерева (число должно быть >= VERTEXES_COUNT).
static int const MAX_VALUE = 999;

/// Private: Функция сравнения двух чисел, которая необходима для сортировки (по возрастанию).
int compare(void const *const, void const *const);

/// Private: Генерация массива уникальных случайных целых чисел заданного размера.
int *random_unique_integers_array(size_t const);

/// Private: Генерация случайного целого числа в заданном диапазоне.
int random_integer(int const, int const);

int main(int const argc, char const *const argv[]) {
	srand((unsigned)time(0));

	tree *tree_a1 = NULL;
	tree *tree_a2 = NULL;

	tree_vertex *const vertexes = (tree_vertex *const)malloc(VERTEXES_COUNT * sizeof(tree_vertex));
	int *const int_array = random_unique_integers_array(VERTEXES_COUNT);

	for (size_t i = 0; i < VERTEXES_COUNT; i++) {
		vertexes[i].value = int_array[i];
		vertexes[i].weight = random_integer(MIN_WEIGHT, MAX_WEIGHT);
		vertexes[i].is_used = false;
	}

	printf("-----------------------------------\n");
	printf("A1:\n");

	a1_insertion(&tree_a1, vertexes, VERTEXES_COUNT);

	int hs_a1 = 0, ws_a1 = 0;
	int const height_a1 = max_height(tree_a1);
	calculate_weight_average_height(tree_a1, height_a1, &hs_a1, &ws_a1);
	double const hcp_a1 = (double)hs_a1 / (double)ws_a1;

	// Обход и вывод дерева.
	// printf("From left to right: ");
	// tree_traversal(tree_a2);

	printf("Weight-average height: %f == (hs=%d / ws=%d)\n", hcp_a1, hs_a1, ws_a1);
	printf("Checksum of tree: %d\n", tree_checksum(tree_a1));

	printf("-----------------------------------\n");
	printf("A2:\n");

	qsort(vertexes, VERTEXES_COUNT, sizeof(tree_vertex), compare);

	int hs_a2 = 0, ws_a2 = 0;
	tree_a2 = a2_insertion(vertexes, 0, VERTEXES_COUNT - 1);
	int const height_a2 = max_height(tree_a2);
	calculate_weight_average_height(tree_a2, height_a2, &hs_a2, &ws_a2);
	double const hcp_a2 = (double)hs_a2 / (double)ws_a2;

	// Обход и вывод дерева.
	// printf("From left to right: ");
	// tree_traversal(tree_a2);

	printf("Weight-average height: %f == (hs=%d / ws=%d)\n", hcp_a2, hs_a2, ws_a2);
	printf("Checksum of tree: %d\n", tree_checksum(tree_a2));

	printf("-----------------------------------\n\n");

	return EXIT_SUCCESS;
}

int compare(void const *const left, void const *const right) {
	int const arg1 = ((tree_vertex const *const)left)->value;
	int const arg2 = ((tree_vertex const *const)right)->value;
	return arg1 - arg2;
}

int *random_unique_integers_array(size_t const array_size) {
	int *const array = (int *const)malloc(array_size * sizeof(int));
	array[0] = random_integer(MIN_VALUE, MAX_VALUE);

	for (size_t i = 1; i < array_size; i++) {
		int random = 0;
		bool is_unique = true;

		while (is_unique) {
			random = random_integer(MIN_VALUE, MAX_VALUE);

			for (size_t j = 0; j < i; j++) {
				is_unique = (array[j] == random);
				if (is_unique) {
					break;
				}
			}
		}

		array[i] = random;
	}

	return array;
}

int random_integer(int const from, int const to) {
	return rand() % (to - from + 1) + from;
}
