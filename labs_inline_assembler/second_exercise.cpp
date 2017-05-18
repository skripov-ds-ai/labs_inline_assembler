// Copyright (c) 2017 Denis Skripov
// https://github.com/nizhikebinesi/labs_inline_assembler
#include "second_exercise.h"

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
	
	// struct Matrix {
	// 	unsigned int n;
	// 	int **arr;
	// };

	Matrix* create_matrix(unsigned int N) {
		Matrix* m;
		__asm {
			;// move to eax size of Matrix type
			mov		eax, size Matrix
			;// push this size to stack
			push	eax
			;// get memory for this structure
			call	dword ptr malloc
			;// clean stack
			add		esp, 4


			cmp		eax, 0
			;// if new Matrix* is nullptr then go to NULL_PTR
			je		NULL_PTR

			;// move N(e.g. size of array in new Matrix)
			mov		ebx, N



			mov		dword ptr [eax], ebx
			;// move new Matrix* to Matrix* m
			mov		m, eax

			;// multiply size of new array by 4
			shl     ebx, 2

			jc		OVER_FLOW

			;// push this number to stack
			push    ebx

			;// get memory for array of pointers(int**)
			call    dword ptr malloc;
			;// clean stack
			add     esp, 4

			;// if eax is zero then to EXIT
			cmp     eax, 0
			je      EXIT_NULL

			;//push this pointer to stack
			push    eax
			;// esi will be counter
			xor     esi, esi

			xor     edi, edi

		CYCLE:
			;// compare counter and size of 2-d array
			cmp     esi, N
			;// if esi == N then return pointer on 2-d array of integers
			je     NEXT

			;// move size of line to eax
			mov     eax, N
			;// multiply size of new array by 4
			shl     eax, 2;

			push    eax

			;// get memory for array of pointers(int*)
			call    dword ptr malloc

			;// clean stack
			add     esp, 4

			;// compare pointer and nullptr
			cmp     eax, 0
			je      MEM_ER

			;// associate new pointer(int*) and real part of memory in exist array
			mov     ebx, [esp]
			mov		[ebx][esi * 4], eax
			inc     esi

			jmp     CYCLE

		NEXT:
			pop		eax
			jmp		EXIT

		MEM_ER:
			;// put count of exist lines to edi
			mov     ecx, esi

		CYCLE_2:
			push    ecx

			mov     eax, [esp]
			mov     eax, [eax][ecx * 4 - 4]

			push    eax

			call    dword ptr free

			add     esp, 4
			pop     ecx

			loop    CYCLE_2

			call    dword ptr free
			add     esp, 4

			jmp		EXIT

		OVER_FLOW:
			mov		dword ptr [eax], 0
			mov		dword ptr [eax + 4], 0
			jmp		FINAL

		EXIT_NULL:
			mov		ebx, m;
			;// move to m->n zero
			mov		dword ptr [ebx], 0

			jmp		FINAL

		EXIT:

			mov		ebx, m
			mov		dword ptr [ebx + 4], eax
			mov		eax, m

		NULL_PTR:
		FINAL:

		}
	}

	// zero if there are no errors else if i or j is not in [0; n) - -1
	int set_i_j_element(int elem, unsigned int j, unsigned int i, Matrix* m) {
		__asm {
			mov		edi, i
			mov		esi, j

			mov		eax, -1

			mov		ebx, m
			mov		ecx, dword ptr [ebx]

			cmp		esi, ecx
			jge		ERR
			cmp		edi, ecx
			jge		ERR
			cmp		esi, eax
			jle		ERR
			cmp		edi, eax
			jle		ERR

			add		ebx, 4

			mov		edx, [ebx]
			mov		ebx, [edx][esi * 4]
			mov		eax, elem
			mov		dword ptr [ebx][edi * 4], eax
			//mov		eax, dword ptr [ebx]
			//mov		temp, eax
			xor		eax, eax
			jmp FINAL

		ERR:
			mov		eax, -1


		FINAL:
		}
	}

	// zero if there are no errors else if i or j is not in [0; n) - -1
	//int get_i_j_element(int* elem, unsigned int j, unsigned int i, Matrix* m) {
	int get_i_j_element(unsigned int j, unsigned int i, const Matrix* m) {
		__asm {
			mov		edi, i
			mov		esi, j

			//mov		eax, -1

			mov		ebx, m
			mov		ecx, dword ptr [ebx]

			/*cmp		esi, ecx
			jge		ERR
			cmp		edi, ecx
			jge		ERR
			cmp		esi, eax
			jle		ERR
			cmp		edi, eax
			jle		ERR*/

			add		ebx, 4

			mov		edx, [ebx]
			mov		ebx, [edx][esi * 4]
			mov		edx, dword ptr [ebx][edi * 4]
			//lea		ebx, elem
			//mov		ebx, edx
			//mov		elem, edx

			//xor		eax, eax
			//jmp FINAL

			//	ERR:
			//mov		eax, -1
			mov		eax, edx

			FINAL :
		}
	}

	void fill_matrix(Matrix* m) {
		char* fmt2 = "%d";
		int temp;
		__asm {

			mov		eax, m

			mov		ecx, dword ptr [eax]

			push	ecx

			push	eax


			xor		esi, esi

		FOR_I:

			cmp		esi, [esp + 4]
			je		NEXT_I

			push	esi

			xor		edi, edi

		FOR_J:

			cmp		edi, [esp + 8]
			je		NEXT_J

			push	edi

			lea		eax, temp
			push	eax
			mov		eax, dword ptr fmt2
			push	eax

			call	dword ptr scanf_s

			add		esp, 8

			mov		ebx, temp
			push	ebx

			call	dword ptr set_i_j_element

			add		esp, 4
			pop		edi
			inc		edi

			jmp		FOR_J
		NEXT_J:

			pop		esi
			inc		esi

			jmp		FOR_I
		NEXT_I:

			add		esp, 8
			jmp		FINAL

		FINAL:

		}
	}

	Matrix* read_from_stdin() {
		char 
			*fmt1 = "%ud", 
			*str1 = "Enter matrix size:\n",
			*str2 = "Enter matrix elements:\n";
		unsigned int n;
		__asm {
			lea		eax, n
			push	eax
			mov		eax, dword ptr fmt1
			push	eax

			mov		eax, dword ptr str1
			push	eax
			call	dword ptr printf
			add		esp, 4

			call	dword ptr scanf_s

			add		esp, 8
			mov		ebx, n
			push	ebx

			shl		eax, 2
			jc		OVER_FLOW

			mov		eax, dword ptr str2
			push	eax
			call	dword ptr printf
			add		esp, 4

			call	dword ptr create_matrix

			add		esp, 4

			cmp		eax, 0
			je		FINAL

			cmp		dword ptr [eax], 0
			je		FINAL

			push	eax

			call	dword ptr fill_matrix

			pop		eax

			jmp		FINAL

		OVER_FLOW:
			add		esp, 4
			xor eax, eax
			jmp		FINAL

		FINAL:

		}
	}

	void erase_matrix(Matrix* m) {

		// проблема в ассемблерном цикле
		//for (int i = 0; i < m->n; i++) {
		//	std::free(m->arr[i]);
		//}
		//std::free(m->arr);
		//std::free(m);

		__asm {

			mov		eax, m

			cmp		eax, 0
			je		FINAL

			mov		ecx, dword ptr [eax]
			cmp		ecx, 0
			je		FINAL

			push	eax

			add		eax, 4
			mov		ebx, [eax]
			mov		eax, ebx

			push	eax

		FOR:

			mov		ebx, [eax][ecx * 4 - 4]

			push	ecx
			push	ebx

			call	dword ptr free
			add		esp, 4

			pop		ecx
			mov		eax, [esp]

			loop FOR

			call	dword ptr free
			add		esp, 4

			call dword ptr free
			add		esp, 4

		FINAL:
		}
		//std::free(m->arr);
		//std::free(m);
	}

	void print_to_stdout(const Matrix* m) {
		char* fmt2 = "%d ";
		char* fmt3 = "\n";
		char* nil = "null\n";
		int temp;
		__asm {

			mov		eax, m

			cmp		eax, 0
			je		NILL

			mov		ecx, dword ptr [eax]

			push	ecx

			push	eax


			xor		esi, esi

		FOR_I:

			cmp		esi, [esp + 4]
			je		NEXT_I

			push	esi

			xor		edi, edi

		FOR_J:

			cmp		edi, [esp + 8]
			je		NEXT_J

			push	edi

			/*lea		eax, temp
			push	eax
			mov		eax, dword ptr fmt2
			push	eax

			call	dword ptr scanf_s

			add		esp, 8*/

			/*mov		ebx, temp
			push	ebx*/

			call	dword ptr get_i_j_element

			push	eax
			push	dword ptr fmt2

			call	dword ptr printf

			add		esp, 8

			/*add		esp, 4*/
			pop		edi


			inc		edi

			jmp		FOR_J
		
		NEXT_J:

			push	dword ptr fmt3

			call	dword ptr printf

			add		esp, 4

			pop		esi
			inc		esi

			jmp		FOR_I
		NEXT_I:

			add		esp, 8
			jmp		FINAL

		NILL:
			mov		eax, nil
			push	eax
			call	dword ptr printf
			add		esp, 4

		FINAL:

		}
	}

	void make_i_j_c(
		unsigned int j, unsigned int i, 
		const Matrix* a, const Matrix* b,
		Matrix* c, unsigned int n) {
		// add overflow catching
		__asm {
			xor		eax, eax
			push	eax // put 0

			mov		ecx, n

		FOR_K:

			push	ecx // put (k + 1)
			mov		eax, a
			push	eax // put a
			mov		eax, i
			push	eax // put i
			mov		eax, ecx
			dec		eax
			push	eax // put k

			call	dword ptr get_i_j_element

			pop		edx // get k
			add		esp, 8 // erase i and a
			push	eax // put a(ik)
			mov		eax, b
			push	eax // put b
			push	edx // put k
			mov		eax, j
			push	eax // put j

			call	dword ptr get_i_j_element

			add		esp, 12 // erase j & k & b
								//pop		ecx
			pop		ebx
			imul	ebx

			pop		ecx
			//jc		OVER_FLOW

			mov		edx, [esp]

			add		edx, eax

			//jc		OVER_FLOW

			mov[esp], edx

			loop	FOR_K

			pop		edx // pop c(ij)

			mov		eax, c
			push	eax // put c

			mov		eax, i
			push	eax // put i

			mov		eax, j
			push	eax // put j

			push	edx // put c(ij)

			call	dword ptr set_i_j_element

			add		esp, 16 // erase c(ij) & j & i & c

		}

	}

	Matrix* mult(const Matrix* b, const Matrix* a) {
		// Matrix* c;
		__asm {
			mov		ebx, b
			cmp		ebx, 0
			je		ZERO_B

			mov		eax, a
			cmp		eax, 0
			je		ZERO_A

			mov		ecx, dword ptr [ebx]
			mov		edx, dword ptr [eax]

			cmp		ecx, edx
			jne		NOT_EQUAL_SIZE

			push	ecx // put size

			call	dword ptr create_matrix

			mov		ecx, [esp]
			push	eax // put c

			mov		eax, b
			push	eax // put b

			mov		eax, a
			push	eax // put a

		FOR_I:

			mov		eax, ecx
			dec		eax
			push	eax // put i

			mov		ecx, [esp + 16]

		FOR_J:

			mov		eax, ecx
			dec		eax
			push	eax // put j

			call	dword ptr make_i_j_c

			pop		ecx // get j
			inc		ecx

			loop	FOR_J

			pop		ecx // get i
			inc		ecx

			loop	FOR_I

			add		esp, 8 // erase
			pop		ebx
			//mov		c, eax
			//mov		eax, c
			add		esp, 4
			mov		eax, ebx

			jmp		FINAL

		NOT_EQUAL_SIZE:
			xor		eax, eax
			jmp		FINAL

		ZERO_A:
			xor		eax, eax
			jmp		FINAL

		ZERO_B:
			xor		eax, eax
			jmp		FINAL

		FINAL:

		}
	}

	/*bool is_nil_matrix(Matrix* m) {
		// if m is null or have m.n = 0 -> 1
		// else -> 0
		__asm {
			mov		ebx, m
			cmp		ebx, 0
			je		NIL
			mov		edx, dword ptr[ebx]
			cmp		edx, 0
			je		NIL
			add		ebx, 4
			mov		ebx, dword ptr[edx]
			cmp		ebx, 0
			je		NIL

			xor		eax, eax

			jmp		FINAL
			NIL :
			mov		eax, 1
				jmp		FINAL
				FINAL :
		}
	}*/
}