// Copyright (c) 2017 Denis Skripov
// https://github.com/nizhikebinesi/labs_inline_assembler
#define _USE_MATH_DEFINES

#include <cstdio>
#include <memory>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <ctime>
#include <cassert>
#include <vector>
#include <string>
#include <cmath>
// including
// my own modules
#include "first_exercise.h"
#include "second_exercise.h"
//
#include <cstring>


using namespace std;
using exercises::Matrix;
using exercises::index_of;
using exercises::index_of_pratt;
using exercises::prefix_function;

const int BUFFER_SIZE = 256;

using namespace std;

double tangent(double x, double epsilon = 1e-5) {
	const int m = 15, n = 2, k = 3;
	const double left = -M_PI_2, right = M_PI_2;
	
	//double xx;
	__asm {
		finit
		xor		eax, eax
		xor		ebx, ebx // флаг, является ли число отрицательным

		fld		qword ptr epsilon // 0 eps
		fld		qword ptr x // 1 x

		// сравниваем с нулем
		fldz

		fcomp
		xor		eax, eax
		fstsw	ax
		sahf

		jna		NON_NEGATIVE

		mov		ebx, 1
		fchs

	NON_NEGATIVE:
		fld		qword ptr right

		fcom
		// xor		eax, eax
		fstsw	ax
		sahf

		jb		RIGHT_LOOP		
		
		//fld		qword ptr left

		//fcom
		//xor		eax, eax
		//fstsw	ax
		//sahf

		//jna		LEFT_LOOP

		jmp		NEXT_LEFT

		//jmp		CALCULATE

	RIGHT_LOOP:

		fsub	st(1), st(0)
		fsub	st(1), st(0)
		fcom
		// xor		eax, eax
		fstsw	ax
		sahf
		ja		NEXT_RIGHT

		jmp		RIGHT_LOOP
	NEXT_RIGHT:
		fstp	st(0)
		jmp		CALCULATE

	LEFT_LOOP:

		fsub	st(1), st(0)
		fsub	st(1), st(0)
		fcom
		//xor		eax, eax
		fstsw	ax
		sahf
		jb		NEXT_LEFT

		jmp		LEFT_LOOP

	NEXT_LEFT:
		fstp	st(0)
		jmp		CALCULATE

	CALCULATE:

		fld		st(2) // 2 eps
		//fld		qword ptr epsilon

		fcomp // 2 eps -> erase
		fstsw	ax
		sahf
		jnb		FIRST_FINAL

		fld		st(0) // 2 x
		fld		st(0) // 3 x
		fmul	st(0), st(1) // 4 x^2
		fld		st(0) // 4 x^2
		fmul	st(0), st(2) // 5 x^3

		fld		st(0)
		fild	dword ptr k
		fdivp	st(1), st(0)
		fadd	st(4), st(0)

		fld		st(5)
		//fld		qword ptr epsilon

		fcomp
		fstsw	ax
		sahf
		ja		SECOND_FINAL

		fstp	st(0)

		fld		st(0) // 5 x^3
		fmul	st(0), st(2) // 5 x^5
		fild	dword ptr n // 6 n
		fmulp	st(1), st(0) // 5 (n * x^5)
		fild	dword ptr m // 6 m
		fdivp	st(1), st(0) // 5 (n * x^5 / m)
		faddp	st(4), st(0) // 
		fstp	st(0)
		fxch	st(2)
		//fstp	st(0)
		jmp		FINAL

	FIRST_FINAL:
		jmp		FINAL

	SECOND_FINAL:
		fxch	st(4)
		jmp		FINAL

	FINAL:

		cmp		ebx, 1
		je		NEGATIVE
		jmp		FIN
	NEGATIVE:
		fchs
		jmp		FIN
	FIN:

	}
	/*
	// валидный код
	__asm {
		finit
		fld		qword ptr x // 0 x
		fld		st(0) // 1 x
		fmul	st(0), st(1) // 1 x^2
		fld		st(0) // 2 x^2
		fmul	st(0), st(2) // 2 x^3
		fld		st(0) // 3 x^3
		fmul	st(0), st(2) // 3 x^5
		fild	dword ptr n // 4 n
		fmulp	st(1), st(0) // 3 (n * x^5)
		fild	dword ptr m // 4 m
		fdivp	st(1), st(0) // 3 (n * x^5 / m)
		faddp	st(3), st(0) // 
		fild	dword ptr k // 4 k
		fdivp	st(1), st(0) // 3 (x^3 / k)
		faddp	st(2), st(0) // 2 (sum)
		fstp	st(0)
	}*/

	/*__asm {
		finit
		
		fld		qword ptr x // result
		
		//fld		qword ptr epsilon // eps
		fld		qword ptr x // x
		fld		qword ptr x // x
		
		fldz // 0
		fadd	st(0), st(1) // x
		fld		qword ptr epsilon
		fcomp	st(1)
		fstsw	ax

		jmp		FINAL

		ja		FIRST


		fmul	st(0), st(1) // x^2

		fld1 // 1
		fmul	st(0), st(1) // x^2
		fmul	st(0), st(2) // x^3

		fldz // 0
		fadd	st(0), st(1) // x^3

		fild	k // 3
		fdivp	st(1), st(0) // (x^3)/3
		
		fld		qword ptr epsilon
		fcomp	st(1) // eps - st(1)
		fstsw	ax

		faddp	st(4), st(0)

		ja		SECOND

		fstp	st(0)

		fld1 // 1
		fmul	st(0), st(1) // x^3
		fmul	st(0), st(2) // x^5

		fild	n
		fmulp	st(1), st(0)
		fild	m
		fdivp	st(1), st(0)

		faddp	st(4), st(0)

		jmp		THIRD

	FIRST:
		fld		st(2)
		jmp		FINAL

	SECOND:
		fld		st(4)
		jmp		FINAL

	THIRD:
		fld		st(3)
		jmp		FINAL

	FINAL:


	}*/
}

char* string_generator(int size) {
	//srand(7);
	char* s = new char[size + 1];
	for (int i = 0; i < size; i++) {
		int c = (rand() % 30 + 50);
		s[i] = (char)c;//((rand() % 100 + 100) % 100 + 50);
	}
	s[size] = '\0';
	return s;
}

void test_index_of() {
	srand(42);
	cout.precision(20);
	const int n = 100;
	int proven, verifiable;
	string s1, s2;
	char *ss1, *ss2;
	for (int i = 0; i < n; i++) {
		ss1 = string_generator(rand() % 500 + 5/*rand() % 50 + 10*/);
		ss2 = string_generator(rand() % 300 + 2/*rand() % 10 + 1)*/);
		///*ss1 =*/ strcpy_s(ss1, 30000, ss2);
		s1 = string(ss1);
		s2 = string(ss2);
		int start1 = clock();
		proven = index_of_pratt(s1, s2);
		int end1 = clock();
		///char *ss1 = s1.c_str() + '\n';//new char [s1.length() + 1];
		///char *ss2 = //new char [s2.length() + 1];
		//strcpy(ss1, s1.c_str());
		//strcpy(ss2, s2.c_str());
		int start2 = clock();
		verifiable = index_of(ss1, ss2);
		int end2 = clock();
		cout << "first = " << s1 << "\nsecond = " << s2 << "\n";
		cout << "index1 = " << proven << "\nindex2 = " << verifiable << "\n";
		cout << "time1 = " << 0.0 + (0.0 + end1 - start1) / 1000
			<< " s\ntime2 = " << 0.0 + (0.0 + end2 - start2) / 1000 << " s\n";
		//printf("first = %s\nsecond = %s\n", s1.c_str, s2.c_str);
		//printf("index1 = %d\nindex2 = %d\n", proven, verifiable);
		if (proven == verifiable) {
			printf("OK!\n");
			//system("pause");
		}
		else {
			printf("Troubles with index_of\n");
			//system("pause");
		}
		//if (!((i + 1) % 7)) {
		system("pause");
		//}
		delete[] ss1;
		delete[] ss2;
	}
}

#define FLUSH_FIRST "%*[^\n]"
#define FLUSH_SECOND "%*c";

/*void __flush() {
char *first = FLUSH_FIRST;
char *second = FLUSH_SECOND;
__asm {
mov		eax, second
push	eax
mov		eax, first
push	eax
call	dword ptr scanf_s
add		esp, 4
call	dword ptr scanf_s
add		esp, 4
}
}*/

int main(void) {
	//srand(7);
	//srand(time(NULL));
	/*char *src = "10123", *tgt = "123";
	int start = clock();
	printf("%d\n", index_of(src, tgt));
	int end = clock();
	printf("time = %.21f\n", (0.0 + end - start) / 1000);
	printf("\n\n");*/
	//delete[] src;
	//delete[] tgt;

	//printf, scanf from __asm and make 

	/* Кроме   того,  программа  должна  иметь  "дружелюбный"
	интерфейс   (например, предлагать  выполнить  повторное  тестирование).  ¬вод
	данных   из   файла    не  требуетс¤,   хот¤   приветствуетс¤.  ¬вод/вывод  с
	консоли   выполн¤ть   с  помощью функций  printf  и  scanf,   вызов   которых
	тоже  должен  происходить   внутри ассемблерных вставок.*/
	
	//cout << ((unsigned int)7 | (~(unsigned int)125 << (unsigned int)3)) << endl;

	const double eps = 1e-1;

	//for (double a = -M_PI; a < M_PI; a += eps) {
		double res = tangent(-atan(1));
		cout << "my_function = " << res << "\n";
		cout << "original_tan = " << tan(-atan(1)) << "\n";
		//system("pause");
	//}

	/*char *welcome = "Welcome!\n";
	char *test_text_1 = "\nEnter the string in which you want to search for:\n";
	char *test_text_2 = "\nEnter the string which you want to search:\n";
	char *error_become = "\nThere is some error with memory\n";
	char *quit = "\nFor \"QUIT\" enter \'y\' else \'n\':\n";



	char *my_pause = "pause";
	char to_exit = 'y';
	char *to_printf = "\nindex_of = %d\n";

	char *src = NULL, *tgt = NULL;


	char is_exit = 0;
	char *for_exit = "%c";
	char *flush_first = FLUSH_FIRST;// "%*[^\n]";//"%*[^\n]%*c";
	char *flush_second = FLUSH_SECOND;//"%*c";
									  //%*[^\n]

									  // проблемы когда src не ввели, а tgt ввели

									  //char scanf_fmt[] = "%c";
									  //char printf_fmt[] = "%c\n";

	int id = 2;

	if (id != 1) {

	}
	else
		_asm
	{

		mov		eax, welcome
		push	eax
		call	dword ptr printf
		add		esp, 4

		BEGIN:

		call	dword ptr flushall

			mov		eax, test_text_1
			push	eax
			call	dword ptr printf
			add		esp, 4



			mov		eax, BUFFER_SIZE
			push	eax
			call	dword ptr malloc
			add		esp, 4
			cmp		eax, 0
			je		MEMORY_ERROR

			mov		src, eax

			mov		eax, BUFFER_SIZE;// записываем сначала N, а потом адрес новой строки
		sub		eax, 1
			push	eax
			mov		eax, src
			;// mov		src, eax
		push	eax
			call	dword ptr gets_s
			add		esp, 8
			;//mov		edx, src
		;//xor		eax, eax
		mov		src, eax

			mov		eax, test_text_2
			push	eax
			call	dword ptr printf
			add		esp, 4

			mov		eax, BUFFER_SIZE
			push	eax
			call	dword ptr malloc
			add		esp, 4
			cmp		eax, 0
			je		MEMORY_ERROR

			mov		tgt, eax

			mov		eax, BUFFER_SIZE
			sub		eax, 1
			push	eax
			mov		eax, tgt
			;// mov		tgt, eax
		push	eax
			call	dword ptr gets_s
			add		esp, 8

			mov		tgt, eax

			;//my function; tgt in eax; src in edx

		;//mov		eax, tgt
		mov		edx, src


			;//ошибка где-то здесь // уже нет, вывод есть

		push	eax
			push	edx
			call	dword ptr index_of
			add		esp, 8
			push	eax
			mov		eax, to_printf
			push	eax
			call	dword ptr printf
			add		esp, 8

			;//free, похоже ошибка здесь
		mov		ebx, tgt
			mov		ecx, src
			push	ebx
			push	ecx
			call	dword ptr free
			add		esp, 4
			//mov		tgt, eax
			call	dword ptr free
			add		esp, 4

			//mov		src, eax
			;//обработка выхода:
		mov		eax, quit
			push	eax
			call	dword ptr printf
			add		esp, 4

			mov		eax, 1
			push	eax
			lea		eax, is_exit
			push	eax
			mov		eax, for_exit
			push	eax
			call	dword ptr scanf_s
			add		esp, 12

			//mov		is_exit, eax
			//mov		eax, dword ptr is_exit
			//mov		ebx, dword ptr to_exit

			//mov		bl, to_exit
			//lea		ebx, to_exit
			//movzx		cl, byte ptr [eax]

			//нужно сделать хороший flush
			//этот flush только 1 символ удал¤ет



			//call	dword ptr __flush

			mov		eax, flush_second
			push	eax
			mov		eax, flush_first
			push	eax
			call	dword ptr scanf_s
			add		esp, 4
			call	dword ptr scanf_s
			add		esp, 4

			//mov		eax, _flush
			//push	eax
			//call	dword ptr scanf_s
			//add		esp, 4
			//call	dword ptr flushall

			lea		eax, is_exit

			cmp		byte ptr[eax], 'y'
			je		EXIT

			jmp		BEGIN

			MEMORY_ERROR :
		mov		eax, error_become
			push	eax
			call	dword ptr printf
			add		esp, 4

			mov		eax, my_pause
			push	eax
			call	dword ptr system
			add		esp, 4
			EXIT:
	}*/


	//test_index_of();
	//Matrix a = Matrix(2);
	/*char *s1 = " \0", *s2 = " \0";
	start = clock();
	printf("%d\n", index_of(s1, s2));
	end = clock();
	printf("time = %.21f\n", (0.0 + end - start) / 1000);
	printf("\n\n");*/
	//delete[] s1;
	//delete[] s2;
	return 0;
}