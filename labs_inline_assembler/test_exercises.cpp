#include "test_exercises.h"
#include "first_exercise.h"
#include "second_exercise.h"
#include "third_exercise.h"

namespace test_exercises {
	using std::cout;
	
	using namespace exercises;
	using exercises::index_of;


	const int BUFFER_SIZE = 256;

	void test_first() {
		//cout << "\nfirst" << "\n";
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

		//int id = 2;

		//if (id != 1) {

		//}
		//else
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
	}

	void second_t();

	void test_second() {
		__asm {
			call	dword ptr second_t
		}
		//cout << "\n\nsecond" << "\n";
	}

	void test_third() {
		//cout << "\n\nthird" << "\n";
		char 
			*str1 = "Enter x:\n",
			*str2 = "Enter eps:\n",
			*fmt = "%lf",
			*ans = "answer = %lf\n";
		// tangent(x, eps);
		double x, eps, answer;
		__asm {
			finit
			mov		eax, dword ptr str1
			push	eax
			call	dword ptr printf
			add		esp, 4

			lea		eax, x
			push	eax
			mov		eax, dword ptr fmt
			push	eax

			// scanf x
			call	dword ptr scanf_s
			add		esp, 8

			mov		eax, dword ptr str2
			push	eax
			call	dword ptr printf
			add		esp, 4

			lea		eax, eps
			push	eax
			mov		eax, dword ptr fmt
			push	eax

			// scanf eps
			call	dword ptr scanf_s
			add		esp, 8


			// проверка eps <= 0 или нет
			// если <= 0 -> default eps
			//finit
			fld		eps
			fldz
			xor		eax, eax
			// 0 - eps
			fcomp
			fstsw	ax
			sahf
			jge		DEFAULT
			jmp		WITH_EPS

		DEFAULT:
			//lea		eax, x
			//push	qword ptr [eax]
			sub		esp, 8
			fld		x
			fstp	qword ptr [esp]
			
			call	tangent
			add		esp, 8
			jmp		PRINT_ANSWER
		
		WITH_EPS:
			sub		esp, 8
			fld		eps
			fstp	qword ptr [esp]
			sub		esp, 8
			fld		x
			fstp	qword ptr[esp]
			//lea		eax, eps
			//push	qword ptr [eax]
			//lea		eax, x
			//push	qword ptr [eax]
			call	tangent
			add		esp, 16
			jmp		PRINT_ANSWER

		PRINT_ANSWER:
			//
			//sub		esp, 8
			//fld		x
			//fstp	qword ptr[esp]
			//
			sub		esp, 8
			fstp		qword ptr [esp]
			//fstp		qword ptr [esp]
			//fst		answer
			//lea		eax, answer
			//push	qword ptr [eax]
			mov		eax, dword ptr ans
			push	eax
			call	printf
			add		esp, 12
		}
	}

	int is_nil(Matrix *m) {
		// if m is null or have m.n = 0 -> 1
		// else -> 0
		__asm {
			mov		ebx, m
			cmp		ebx, 0
			je		NIL
			mov		edx, dword ptr[ebx]
			cmp		edx, 0
			je		NIL
			mov		eax, [ebx]
			add		eax, 4
			//mov		eax, edx
			cmp		eax, 0
			je		NIL

			xor		eax, eax

			jmp		FINAL
			NIL :
			mov		eax, 1
				jmp		FINAL
				FINAL :
		}
		//return false;
	}

	/*void f(Matrix &*x) {

	}*/

	Matrix* f1(/*Matrix *a*/) {
		char
			*fmt = "%ud",
			*s1 = "Enter size of matrix:\n";
		unsigned int n;
		//a = create_matrix(1);
		//Matrix *m;
		__asm {
			mov		eax, dword ptr s1
			push	eax
			call	dword ptr printf
			add		esp, 4

			lea		eax, n
			push	eax
			mov		eax, fmt
			push	eax
			call	dword ptr scanf_s
			add		esp, 8

			mov		eax, n
			push	eax
			call	dword ptr create_matrix

			//mov		ebx, a
			//mov		[ebx], eax

			add		esp, 4

		}
	}

	Matrix* f2(/*Matrix *a*/) {
		__asm {
			call	dword ptr read_from_stdin
			/*mov		ebx, a
			mov		[ebx], eax*/
		}
	}

	void f3(Matrix *a) {
		unsigned int i/*, j*/;
		int value;
		char
			*fmt1 = "%ud",
			*fmt2 = "%d",
			*str1 = "Enter i:\n",
			*str2 = "Enter j:\n",
			*str3 = "Enter value:\n";
		/*scanf_s(fmt1, &i);
		scanf_s(fmt1, &j);
		scanf_s(fmt2, &value);*/

		//set_i_j_element(value, j, i, a);
		__asm {
			mov		eax, a
			push	eax

			mov		eax, dword ptr str1
			push	eax
			call	dword ptr printf
			add		esp, 4

			lea		eax, i
			push	eax
			mov		eax, dword ptr fmt1
			push	eax
			call	dword ptr scanf_s
			add		esp, 8

			mov		eax, i
			push	eax

			mov		eax, dword ptr str2
			push	eax
			call	dword ptr printf
			add		esp, 4

			//lea		eax, j
			lea		eax, i
			push	eax
			mov		eax, dword ptr fmt1
			push	eax
			call	dword ptr scanf_s
			add		esp, 8

			mov		eax, i
			push	eax

			mov		eax, dword ptr str3
			push	eax
			call	dword ptr printf
			add		esp, 4

			lea		eax, value
			push	eax
			mov		eax, dword ptr fmt2
			push	eax
			call	dword ptr scanf_s
			add		esp, 8

			mov		eax, value
			push	eax

			call	dword ptr set_i_j_element
			add		esp, 16
		}
	}

	void f4(Matrix *a) {
		// erase_matrix()
		__asm {
			mov		eax, a
			push	eax
			call	dword ptr erase_matrix
			add		esp, 4
		}
	}

	void f5(Matrix *a) {
		//print_to_stdout(a);
		__asm {
			mov		eax, a
			push	eax
			call	dword ptr print_to_stdout
			add		esp, 4
		}
	}

	void f6(Matrix *a) {
		char
			*s1 = "null\n",
			*s2 = "not null\n";
		__asm {
			mov		eax, a
			push	eax
			call	dword ptr is_nil
			add		esp, 4
			cmp		eax, 1
			je		NIL

			mov		eax, s2
			push	eax
			call	dword ptr printf
			add		esp, 4
			jmp		FINAL
		NIL :
			mov		eax, s1
			push	eax
			call	dword ptr printf
			add		esp, 4
			jmp		FINAL
		FINAL :
		}
	}

	Matrix* f7(/*Matrix *b*/) {
		char
			*fmt = "%ud",
			*s = "Enter size of matrix:\n";
		unsigned int n;
		__asm {
			mov		eax, dword ptr s
			push	eax
			call	dword ptr printf
			add		esp, 4

			lea		eax, n
			push	eax
			mov		eax, fmt
			push	eax
			call	dword ptr scanf_s
			add		esp, 8

			mov		eax, n
			push	eax
			call	dword ptr create_matrix
			/*mov		ebx, b
			mov		[ebx], eax*/
			add		esp, 4
		}
	}

	Matrix* f8(/*Matrix *b*/) {
		__asm {
			call	dword ptr read_from_stdin
			/*mov		ebx, b
			mov		[ebx], eax*/
		}
	}

	void f9(Matrix *b) {
		unsigned int i;
		int value;
		char
			*fmt1 = "%ud",
			*fmt2 = "%d",
			*str1 = "Enter i:\n",
			*str2 = "Enter j:\n",
			*str3 = "Enter value:\n";
		// set_i_j_element(value, j, i, a)
		__asm {
			mov		eax, b
			push	eax

			mov		eax, dword ptr str1
			push	eax
			call	dword ptr printf
			add		esp, 4

			lea		eax, i
			push	eax
			mov		eax, dword ptr fmt1
			push	eax
			call	dword ptr scanf_s
			add		esp, 8

			mov		eax, i
			push	eax

			mov		eax, dword ptr str2
			push	eax
			call	dword ptr printf
			add		esp, 4

			//lea		eax, j
			lea		eax, i
			push	eax
			mov		eax, dword ptr fmt1
			push	eax
			call	dword ptr scanf_s
			add		esp, 8

			mov		eax, i
			push	eax

			mov		eax, dword ptr str3
			push	eax
			call	dword ptr printf
			add		esp, 4

			lea		eax, value
			push	eax
			mov		eax, dword ptr fmt2
			push	eax
			call	dword ptr scanf_s
			add		esp, 8

			mov		eax, value
			push	eax

			call	dword ptr set_i_j_element
			add		esp, 16
		}
	}

	void f10(Matrix **b) {
		// erase_matrix()
		__asm {
			mov		eax, b
			push	eax
			call	dword ptr erase_matrix
			add		esp, 4
		}
	}

	void f11(Matrix *b) {
		// print_to_stdout(b)
		__asm {
			mov		eax, b
			push	eax
			call	dword ptr print_to_stdout
			add		esp, 4
		}
	}

	void f12(Matrix *b) {
		char
			*s1 = "null\n",
			*s2 = "not null\n";
		__asm {
			mov		eax, b
			push	eax
			call	dword ptr is_nil
			add		esp, 4
			cmp		eax, 1
			je		NIL

			mov		eax, s2
			push	eax
			call	dword ptr printf
			add		esp, 4
			jmp		FINAL
			NIL :
			mov		eax, s1
				push	eax
				call	dword ptr printf
				add		esp, 4
				jmp		FINAL
				FINAL :
		}
	}

	void f13(Matrix *b, Matrix *a) {
		// Matrix *c = mult(b, a);
		// print_to_stdout(c);
		// erase_matrix(c);
		__asm {
			mov		eax, b
			push	eax
			mov		eax, a
			push	eax

			call	dword ptr mult
			add		esp, 8

			push	eax
			call	dword ptr print_to_stdout

			call	dword ptr erase_matrix
			add		esp, 4
		}
	}

	void clean() {
		char *fmt = "cls";
		__asm {
			mov		eax, dword ptr fmt
			push	eax
			call	dword ptr system
			add		esp, 4
		}
	}

	void call_punkt(unsigned int punkt, Matrix *b, Matrix *a) {
		__asm {

			call	dword ptr clean

			mov		eax, punkt

			cmp		eax, 1
			je		F1

			cmp		eax, 2
			je		F2

			cmp		eax, 3
			je		F3

			cmp		eax, 4
			je		F4

			cmp		eax, 5
			je		F5

			cmp		eax, 6
			je		F6

			cmp		eax, 7
			je		F7

			cmp		eax, 8
			je		F8

			cmp		eax, 9
			je		F9

			cmp		eax, 10
			je		F10

			cmp		eax, 11
			je		F11
			jmp		FINAL

			cmp		eax, 12
			je		F11
			jmp		FINAL

			cmp		eax, 13
			je		F11
			jmp		FINAL

			F1 :
			mov		eax, a
				push	eax
				call	dword ptr f1
				add		esp, 4
				jmp		FINAL

				F2 :
			mov		eax, a
				push	eax
				call	dword ptr f2
				add		esp, 4
				jmp		FINAL

				F3 :
			mov		eax, a
				push	eax
				call	dword ptr f3
				add		esp, 4
				jmp		FINAL

				F4 :
			mov		eax, a
				push	eax
				call	dword ptr f4
				add		esp, 4
				jmp		FINAL

				F5 :
			mov		eax, a
				push	eax
				call	dword ptr f5
				add		esp, 4
				jmp		FINAL

				F6 :
			mov		eax, a
				push	eax
				call	dword ptr f6
				add		esp, 4
				jmp		FINAL

				F7 :
			mov		eax, b
				push	eax
				call	dword ptr f7
				add		esp, 4
				jmp		FINAL

				F8 :
			mov		eax, b
				push	eax
				call	dword ptr f8
				add		esp, 4
				jmp		FINAL

				F9 :
			mov		eax, b
				push	eax
				call	dword ptr f9
				add		esp, 4
				jmp		FINAL

				F10 :
			mov		eax, b
				push	eax
				call	dword ptr f10
				add		esp, 4
				jmp		FINAL

				F11 :
			mov		eax, b
				push	eax
				call	dword ptr f11
				add		esp, 4
				jmp		FINAL

				F12 :
			mov		eax, b
				push	eax
				call	dword ptr f12
				add		esp, 4
				jmp		FINAL

				F13 :
			mov		eax, a
				push	eax
				mov		eax, b
				push	eax
				call	dword ptr f13
				add		esp, 8
				jmp		FINAL

				FINAL :
		}
	}

	unsigned int second_menu(Matrix **a, Matrix **b) {
		//bool exit = false;
		unsigned int punkt;
		char* fmt = "%ud";
		__asm {
			lea		eax, punkt
			push	eax
			mov		eax, dword ptr fmt
			push	eax

			call	dword ptr scanf_s

			add		esp, 8

			mov		eax, punkt
			cmp		punkt, 0

			je		EXIT_TRUE

			mov		ebx, a
			push	ebx
			mov		ebx, b
			push	ebx

			push	eax


			call	dword ptr clean

			//mov		eax, punkt

			pop		eax

			cmp		eax, 1
			je		F1

			cmp		eax, 2
			je		F2

			cmp		eax, 3
			je		F3

			cmp		eax, 4
			je		F4

			cmp		eax, 5
			je		F5

			cmp		eax, 6
			je		F6

			cmp		eax, 7
			je		F7

			cmp		eax, 8
			je		F8

			cmp		eax, 9
			je		F9

			cmp		eax, 10
			je		F10

			cmp		eax, 11
			je		F11

			cmp		eax, 12
			je		F12

			cmp		eax, 13
			je		F13
			jmp		FINAL

			F1 :
			/*mov		eax, a
			push	eax*/
			call	dword ptr f1
				/*add		esp, 4*/
				jmp		FINAL

				F2 :
			/*mov		eax, a
			push	eax*/
			call	dword ptr f2
				/*add		esp, 4*/
				jmp		FINAL

				F3 :
			/*mov		eax, a
			push	eax*/
			call	dword ptr f3
				/*add		esp, 4*/
				jmp		FINAL

				F4 :
			/*mov		eax, a
			push	eax*/
			call	dword ptr f4
				/*add		esp, 4*/
				jmp		FINAL

				F5 :
			/*mov		eax, a
			push	eax*/
			call	dword ptr f5
				/*add		esp, 4*/
				jmp		FINAL

				F6 :
			/*mov		eax, a
			push	eax*/
			call	dword ptr f6
				/*add		esp, 4*/
				jmp		FINAL

				F7 :
			/*mov		eax, b
			push	eax*/
			call	dword ptr f7
				/*add		esp, 4*/
				jmp		FINAL

				F8 :
			/*mov		eax, b
			push	eax*/
			call	dword ptr f8
				/*add		esp, 4*/
				jmp		FINAL

				F9 :
			/*mov		eax, b
			push	eax*/
			call	dword ptr f9
				/*add		esp, 4*/
				jmp		FINAL

				F10 :
			/*mov		eax, b
			push	eax*/
			call	dword ptr f10
				/*add		esp, 4*/
				jmp		FINAL

				F11 :
			/*mov		eax, b
			push	eax*/
			call	dword ptr f11
				/*add		esp, 4*/
				jmp		FINAL

				F12 :
			/*mov		eax, b
			push	eax*/
			call	dword ptr f12
				/*add		esp, 4*/
				jmp		FINAL

				F13 :
			/*mov		eax, a
			push	eax
			mov		eax, b
			push	eax*/
			call	dword ptr f13
				//add		esp, 8
				jmp		FINAL

				FINAL :

			//	add		esp, 4

			//
			//add		esp, 8
			//

			xor		eax, eax
				jmp		FIN

				EXIT_TRUE :
			mov		eax, 1
				jmp		FIN
				FIN :
		}
	}

	void print_second_menu() {
		const int N = 14;
		char *s[N] = {
			"0) EXIT\n",
			"1) Create a matrix\n",
			"2) Read a matrix from stdin(&create)\n",
			"3) Set a(i, j) element\n",
			"4) Erase a matrix\n",
			"5) Print a matrix\n",
			"6) (Optional) Is a matrix null ?\n",
			"7) Create b matrix\n",
			"8) Read b matrix from stdin(&create)\n",
			"9) Set b(i, j) element\n",
			"10) Erase b matrix\n",
			"11) Print b matrix\n",
			"12) (Optional) Is b matrix null ? \n",
			"13) (Variant) product of a and b(c = a * b; return new Matrix)\n"
		};

		char
			*s0 = "0) EXIT\n",
			*s1 = "1) Create a matrix\n",
			*s2 = "2) Read a matrix from stdin(&create)\n",
			*s3 = "3) Set a(i, j) element\n",
			*s4 = "4) Erase a matrix\n",
			*s5 = "5) Print a matrix\n",
			*s6 = "6) (Optional) Is a matrix null ?\n",
			*s7 = "7) Create b matrix\n",
			*s8 = "8) Read b matrix from stdin(&create)\n",
			*s9 = "9) Set b(i, j) element\n",
			*s10 = "10) Erase b matrix\n",
			*s11 = "11) Print b matrix\n",
			*s12 = "12) (Optional) Is b matrix null ? \n",
			*s13 = "13) (Variant) product of a and b(c = a * b; return new Matrix)\n";

		char *cls = "cls";

		__asm {
			mov		eax, cls
			push	eax
			call	dword ptr system
			add		esp, 4

			mov		eax, s0
			push	eax
			call	dword ptr printf
			add		esp, 4

			mov		eax, s1
			push	eax
			call	dword ptr printf
			add		esp, 4

			mov		eax, s2
			push	eax
			call	dword ptr printf
			add		esp, 4

			mov		eax, s3
			push	eax
			call	dword ptr printf
			add		esp, 4

			mov		eax, s4
			push	eax
			call	dword ptr printf
			add		esp, 4

			mov		eax, s5
			push	eax
			call	dword ptr printf
			add		esp, 4

			mov		eax, s6
			push	eax
			call	dword ptr printf
			add		esp, 4

			mov		eax, s7
			push	eax
			call	dword ptr printf
			add		esp, 4

			mov		eax, s8
			push	eax
			call	dword ptr printf
			add		esp, 4

			mov		eax, s9
			push	eax
			call	dword ptr printf
			add		esp, 4

			mov		eax, s10
			push	eax
			call	dword ptr printf
			add		esp, 4

			mov		eax, s11
			push	eax
			call	dword ptr printf
			add		esp, 4

			mov		eax, s12
			push	eax
			call	dword ptr printf
			add		esp, 4

			mov		eax, s13
			push	eax
			call	dword ptr printf
			add		esp, 4


			/*	mov		ecx, N
			mov		eax, s
			mov		ebx, [eax]
			FOR:
			push	ebx
			push	ecx
			mov		eax, dword ptr [ebx][4 * ecx - 4]

			push	eax
			call	dword ptr printf
			add		esp, 4

			pop		ecx
			pop		ebx
			loop	FOR*/
		}
	}

	void second_t() {

		char *my_pause = "pause";
		char *flush_first = FLUSH_FIRST;// "%*[^\n]";//"%*[^\n]%*c";
		char *flush_second = FLUSH_SECOND;//"%*c";
										  //%*[^\n]

		unsigned int punkt = 0;

		Matrix *a = nullptr, *b = nullptr;

		char* fmt = "%ud";

		_asm
		{
			mov		eax, b
			push	eax

			/*call	dword ptr f1
			add		esp, 4*/
			mov		eax, a
			push	eax
			BEGIN :

			call	dword ptr print_second_menu


				lea		eax, punkt
				push	eax
				mov		eax, dword ptr fmt
				push	eax

				call	dword ptr scanf_s

				add		esp, 8

				mov		eax, punkt
				cmp		punkt, 0

				je		EXIT_TRUE

				/*mov		ebx, a
				push	ebx
				mov		ebx, b
				push	ebx*/

				push	eax


				call	dword ptr clean

				//mov		eax, punkt

				pop		eax

				cmp		eax, 1
				je		F1

				cmp		eax, 2
				je		F2

				cmp		eax, 3
				je		F3

				cmp		eax, 4
				je		F4

				cmp		eax, 5
				je		F5

				cmp		eax, 6
				je		F6

				cmp		eax, 7
				je		F7

				cmp		eax, 8
				je		F8

				cmp		eax, 9
				je		F9

				cmp		eax, 10
				je		F10

				cmp		eax, 11
				je		F11

				cmp		eax, 12
				je		F12

				cmp		eax, 13
				je		F13
				jmp		FINAL

				F1 :
			/*mov		eax, a
			push	eax*/
			call	dword ptr f1
				mov[esp], eax
				/*add		esp, 4*/
				jmp		FINAL

				F2 :
			/*mov		eax, a
			push	eax*/
			call	dword ptr f2
				mov[esp], eax
				/*add		esp, 4*/
				jmp		FINAL

				F3 :
			/*mov		eax, a
			push	eax*/
			call	dword ptr f3
				/*add		esp, 4*/
				jmp		FINAL

				F4 :
			/*mov		eax, a
			push	eax*/
			call	dword ptr f4
				xor		eax, eax
				mov[esp], eax
				/*add		esp, 4*/
				jmp		FINAL

				F5 :
			/*mov		eax, a
			push	eax*/
			call	dword ptr f5
				/*add		esp, 4*/
				jmp		FINAL

				F6 :
			/*mov		eax, a
			push	eax*/
			call	dword ptr f6
				/*add		esp, 4*/
				jmp		FINAL

				// for b
				F7 :
			/*mov		eax, b
			push	eax*/
			call	dword ptr f7
				mov[esp + 4], eax
				/*add		esp, 4*/
				jmp		FINAL

				F8 :
			/*mov		eax, b
			push	eax*/
			call	dword ptr f8
				mov[esp + 4], eax
				/*add		esp, 4*/
				jmp		FINAL

				F9 :
			/*mov		eax, b
			push	eax*/
			mov		eax, [esp + 4]
				mov		ebx, [esp]
				mov[esp], eax
				mov[esp + 4], ebx

				call	dword ptr f9

				mov		eax, [esp + 4]
				mov		ebx, [esp]
				mov[esp], eax
				mov[esp + 4], ebx
				/*add		esp, 4*/
				jmp		FINAL

				F10 :
			/*mov		eax, b
			push	eax*/
			mov		eax, [esp + 4]
				mov		ebx, [esp]
				mov[esp], eax
				mov[esp + 4], ebx

				call	dword ptr f10

				xor		eax, eax
				mov[esp], eax

				mov		eax, [esp + 4]
				mov		ebx, [esp]
				mov[esp], eax
				mov[esp + 4], ebx
				/*add		esp, 4*/
				jmp		FINAL

				F11 :
			/*mov		eax, b
			push	eax*/

			mov		eax, [esp + 4]
				mov		ebx, [esp]
				mov[esp], eax
				mov[esp + 4], ebx

				call	dword ptr f11

				mov		eax, [esp + 4]
				mov		ebx, [esp]
				mov[esp], eax
				mov[esp + 4], ebx
				/*add		esp, 4*/
				jmp		FINAL

				F12 :
			/*mov		eax, b
			push	eax*/

			mov		eax, [esp + 4]
				mov		ebx, [esp]
				mov[esp], eax
				mov[esp + 4], ebx

				call	dword ptr f12

				mov		eax, [esp + 4]
				mov		ebx, [esp]
				mov[esp], eax
				mov[esp + 4], ebx
				/*add		esp, 4*/
				jmp		FINAL

				F13 :
			/*mov		eax, a
			push	eax
			mov		eax, b
			push	eax*/
			call	dword ptr f13
				//add		esp, 8
				jmp		FINAL

				FINAL :

			//	add		esp, 4

			//
			//add		esp, 8
			//

			xor		eax, eax
				jmp		FIN

				EXIT_TRUE :
			mov		eax, 1
				jmp		FIN
				FIN :


			cmp		eax, 1
				je		EXIT

				mov		eax, my_pause
				push	eax
				call	dword ptr system
				add		esp, 4

				jmp		BEGIN

				EXIT :
			call	dword ptr erase_matrix
			add		esp, 4
			call	dword ptr erase_matrix
			add		esp, 4
		}
	}

}