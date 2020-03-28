//
//  tree.h
//  NearlyOptimalSearchTree
//
//  Created by Букшев Иван Евгеньевич on 25/03/2020.
//  Copyright © 2020 TA. All rights reserved.
//

#ifndef tree_h
#define tree_h

#include <stdio.h>
#include <stdbool.h>

/// Структура, которая хранит метадату узла дерева (вершина).
typedef struct tree_vertex {
	/// Значение в узле.
	int value;
	/// Вес узла.
	int weight;
	/// Был ли использован.
	bool is_used;

} tree_vertex;

/// Структура, описывающая один узел дерева (который тоже может является деревом).
typedef struct tree {
	/// Высота текущего дерева, относительно корня.
	int height;
	/// Метадата текущего узла.
	tree_vertex vertex;
	/// Левое поддерево.
	struct tree *left;
	/// Правое поддерево.
	struct tree *right;

} tree;

/// Посчитать значение высоты для входного дерева и выставить значение в структуру.
void calculate_and_set_tree_height(tree *const);

/// Прочитать значение высоты, которое хранится в структуре tree. Обычный getter.
int read_tree_height(tree const *const);

/// Посчитать максимально возможную высоту дерева (среди всех поддеревьев).
int max_height(tree const *const);

/// Определить среднюю высоту входного дерева.
double tree_average_height(tree const *const);

/// Определить среднюю размерность входного дерева.
int tree_dimension(tree const *const);

/// Вычислить контрольную сумма входного дерева.
int tree_checksum(tree const *const);

/// Обход дерева. Осуществляется слева-направо: левое поддерево, корень, правое поддерево.
void tree_traversal(tree const *const);

/// Посчитать и записать по указателям средневзвешанную высоту.
void calculate_weight_average_height(tree const *const, int const, int *const, int *const);

#endif /* tree_h */
