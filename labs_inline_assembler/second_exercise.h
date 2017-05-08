// Copyright (c) 2017 Denis Skripov
// https://github.com/nizhikebinesi/labs_inline_assembler
#pragma once

#include <cstdio>
#include <memory>
#include <cstdlib>

namespace exercises {
	// Задачи  этой  группы  предполагают работу с целочисленными  квадратными
	// матрицами, хранящимися  в  виде структуры.Способ  представления  матрицы  в
	// памяти  указывается  в  задании.С помощью ассемблерных  вставок  необходимо
	// реализовать  функции : 1)создать матрицу; 2)удалить матрицу;  3)прочитать, 4)изменить
	// элемент, стоящий на пересечении i - той строки и j - го столбца; 5)печать матрицы;
	// функции, которая описывается в задании.
	//
	// Exercise:
	// Написать операцию умножения матрицы, считая, что матрица представлена в
	// памяти массивом столбцов.
	struct Matrix {
		unsigned int n;
		int **arr;
	};

	Matrix* create_matrix(unsigned int N);

	// zero if there are no errors else if i or j is not in [0; n) - -1
	int set_i_j_element(int elem, unsigned int j, unsigned int i, Matrix* m);

	// zero if there are no errors else if i or j is not in [0; n) - -1
	//int get_i_j_element(int* elem, unsigned int j, unsigned int i, Matrix* m) {
	int get_i_j_element(unsigned int j, unsigned int i, const Matrix* m);

	void fill_matrix(Matrix* m);

	Matrix* read_from_stdin();

	void erase_matrix(Matrix* m);

	void print_to_stdout(const Matrix* m);

	void make_i_j_c(
		unsigned int j, unsigned int i,
		const Matrix* a, const Matrix* b,
		Matrix* c, unsigned int n);

	Matrix* mult(const Matrix* b, const Matrix* a);

}