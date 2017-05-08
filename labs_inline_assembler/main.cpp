// Copyright (c) 2017 Denis Skripov
// https://github.com/nizhikebinesi/labs_inline_assembler
#include <cstdio>
#include <memory>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <ctime>
#include <cassert>
#include <vector>
#include <string>
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
	const int n = 5, k = 3;
	double xx;
	__asm {
		finit

		//fld		qword ptr epsilon // eps
		fld		qword ptr x // x
		fld		qword ptr x // x
		fmul	st(0), st(1) // x^2

		fld		1 // 1
		fmul	st(0), st(1) // x^2
		fmul	st(0), st(2) // x^3

		fld		1 // 1
		fmul	st(0), st(1) // x^3
		fmul	st(0), st(2) // x^5





	}
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

	/* роме   того,  программа  должна  иметь  "дружелюбный"
	интерфейс   (например, предлагать  выполнить  повторное  тестирование).  ¬вод
	данных   из   файла    не  требуетс¤,   хот¤   приветствуетс¤.  ¬вод/вывод  с
	консоли   выполн¤ть   с  помощью функций  printf  и  scanf,   вызов   которых
	тоже  должен  происходить   внутри ассемблерных вставок.*/
	char *welcome = "Welcome!\n";
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
	}


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