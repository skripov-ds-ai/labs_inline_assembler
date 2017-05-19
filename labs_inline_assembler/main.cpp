// Copyright (c) 2017 Denis Skripov
// https://github.com/nizhikebinesi/labs_inline_assembler
#define _USE_MATH_DEFINES

// допиши exercise3, округления, деление и т.п.

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
#include "third_exercise.h"
#include "test_exercises.h"
//
#include <cstring>

#include <fstream>
#include <Windows.h>
#include <conio.h>

#define PTR "-> "
#define SPC "   "
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

using namespace std;
using namespace exercises;
using namespace test_exercises;
/*using exercises::Matrix;
using exercises::index_of;
using exercises::index_of_pratt;
using exercises::prefix_function;
using exercises::tangent;*/

const int BUFFER_SIZE = 256;

int punkt = 0;
int x = 0;
int y = 0;

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

#define NEW_LINE "\n"
#define FLUSH_FIRST "%*[^\n]"
#define FLUSH_SECOND "%*c";



vector<string> create_menu() {
	vector<string> menu;
	string s;
	ifstream fcin;
	fcin.open("C:\\Users\\1\\Documents\\GitHub\\labs_inline_assembler\\labs_inline_assembler\\menu.txt");
	while (getline(fcin, s)) {
		menu.push_back(s);
	}
	fcin.close();
	return menu;
}

vector<string> create_text_before(int &y) {
	vector<string> before;
	string s;
	ifstream fcin;
	fcin.open("C:\\Users\\1\\Documents\\GitHub\\labs_inline_assembler\\labs_inline_assembler\\before.txt");
	while (getline(fcin, s)) {
		before.push_back(s);
		y++;
	}
	y++;
	fcin.close();
	return before;
}

enum ConsoleColor {
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

const WORD	normal = (WORD)(Black << 4) | White, 
			selected = (WORD)(Black << 4) | Yellow,
			testing = (WORD)(Black << 4) | Red;

void gotoxy(int xpos, int ypos) {
	COORD scrn;

	//HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);

	scrn.X = xpos; scrn.Y = ypos;

	SetConsoleCursorPosition(hConsole, scrn);
}

void draw_before_and_menu(const vector<string> &menu, const vector<string> &before, int x, int y) {
	system("cls");
	system("color 00");

	SetConsoleTextAttribute(hConsole, normal);

	/*vector<string>	before = create_text_before(),
		menu = create_menu();*/
	for (auto i = 0; i < before.size(); i++) {
		cout << before[i] << NEW_LINE;
		//y++;
	}
	cout << NEW_LINE;
	//y++;
	for (auto i = 0; i < menu.size(); i++) {
		cout << SPC << menu[i] << NEW_LINE;
	}
}

void draw_menu_punkt(int punkt, const vector<string> &menu, int x, int y) {
	gotoxy(x + 3, y + punkt);
	cout << menu[punkt];
	//SetConsoleTextAttribute(hConsole, selected);
	//gotoxy(x, y + punkt);
	//cout << menu[0];
	//SetConsoleTextAttribute(hConsole, normal);
}

void my_flush() {
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
}

const int N = 3;

vector<test_exercises::test_exercise *> test_punkts() {
	vector<test_exercises::test_exercise *> tests(N);
	tests[0] = new test_exercises::test_exercise_1/*()*/;
	tests[1] = new test_exercises::test_exercise_2/*()*/;
	tests[2] = new test_exercises::test_exercise_3/*()*/;
	return tests;
}

void draw_color_punkt(const vector<string> &menu, HANDLE &hConsole, int x, int y, int punkt, WORD color, char* str) {
	gotoxy(x, y + punkt);
	cout << str;
	draw_menu_punkt(punkt, menu, x, y);
	SetConsoleTextAttribute(hConsole, color);
}

void punkt_move(char ch, int MOD, const vector<string> &menu, HANDLE &hConsole, int x, int y, int &punkt) {
	if (ch == 80) {
		draw_color_punkt(menu, hConsole, x, y, punkt, selected, SPC);

		punkt = ((punkt + 1) % MOD + MOD) % MOD;

		draw_color_punkt(menu, hConsole, x, y, punkt, normal, PTR);
	}
	else if (ch == 72) {
		draw_color_punkt(menu, hConsole, x, y, punkt, selected, SPC);

		punkt = ((punkt - 1) % MOD + MOD) % MOD;

		draw_color_punkt(menu, hConsole, x, y, punkt, normal, PTR);
	}
}

bool break_cycle(char ch, int punkt, const vector<string> &menu) {
	bool condition = (ch == 27) ||  (ch == 13 && punkt == menu.size() - 1);
	return condition;
}

void do_punkt(
	char ch, int x, int y, int &punkt,
	HANDLE &hConsole,
	const vector<test_exercises::test_exercise *> &tests, 
	const vector<string> &before,
	const vector<string> &menu
) {
	if (!(ch == 13 && punkt < tests.size())) {
		return;
	}
	
	{
		gotoxy(x, y);

		system("cls");

		(*tests[punkt])();

		system("pause");

		SetConsoleTextAttribute(hConsole, testing);
		draw_before_and_menu(menu, before, x, y);

		SetConsoleTextAttribute(hConsole, selected);
		draw_color_punkt(menu, hConsole, x, y, punkt, normal, PTR);
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
	NIL:
		mov		eax, 1
		jmp		FINAL
	FINAL:
	}
	//return false;
}

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
	NIL:
		mov		eax, s1
		push	eax
		call	dword ptr printf
		add		esp, 4
		jmp		FINAL
	FINAL:
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

	F1:
		mov		eax, a
		push	eax
		call	dword ptr f1
		add		esp, 4
		jmp		FINAL

	F2:
		mov		eax, a
		push	eax
		call	dword ptr f2
		add		esp, 4
		jmp		FINAL

	F3:
		mov		eax, a
		push	eax
		call	dword ptr f3
		add		esp, 4
		jmp		FINAL

	F4:
		mov		eax, a
		push	eax
		call	dword ptr f4
		add		esp, 4
		jmp		FINAL

	F5:
		mov		eax, a
		push	eax
		call	dword ptr f5
		add		esp, 4
		jmp		FINAL

	F6:
		mov		eax, a
		push	eax
		call	dword ptr f6
		add		esp, 4
		jmp		FINAL

	F7:
		mov		eax, b
		push	eax
		call	dword ptr f7
		add		esp, 4
		jmp		FINAL

	F8:
		mov		eax, b
		push	eax
		call	dword ptr f8
		add		esp, 4
		jmp		FINAL

	F9:
		mov		eax, b
		push	eax
		call	dword ptr f9
		add		esp, 4
		jmp		FINAL

	F10:
		mov		eax, b
		push	eax
		call	dword ptr f10
		add		esp, 4
		jmp		FINAL

	F11:
		mov		eax, b
		push	eax
		call	dword ptr f11
		add		esp, 4
		jmp		FINAL

	F12:
		mov		eax, b
		push	eax
		call	dword ptr f12
		add		esp, 4
		jmp		FINAL

	F13:
		mov		eax, a
		push	eax
		mov		eax, b
		push	eax
		call	dword ptr f13
		add		esp, 8
		jmp		FINAL

	FINAL:
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

	EXIT_TRUE:
		mov		eax, 1
		jmp		FIN
	FIN:
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
	BEGIN:

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

		F1:
			/*mov		eax, a
			push	eax*/
			call	dword ptr f1
			mov		[esp], eax
			/*add		esp, 4*/
			jmp		FINAL

		F2:
			/*mov		eax, a
			push	eax*/
			call	dword ptr f2
			mov		[esp], eax
			/*add		esp, 4*/
			jmp		FINAL

		F3:
			/*mov		eax, a
			push	eax*/
			call	dword ptr f3
			/*add		esp, 4*/
			jmp		FINAL

		F4:
			/*mov		eax, a
			push	eax*/
			call	dword ptr f4
			xor		eax, eax
			mov		[esp], eax
			/*add		esp, 4*/
			jmp		FINAL

		F5:
			/*mov		eax, a
			push	eax*/
			call	dword ptr f5
			/*add		esp, 4*/
			jmp		FINAL

		F6:
			/*mov		eax, a
			push	eax*/
			call	dword ptr f6
			/*add		esp, 4*/
			jmp		FINAL

		// for b
		F7:
			/*mov		eax, b
			push	eax*/
			call	dword ptr f7
			mov		[esp + 4], eax
			/*add		esp, 4*/
			jmp		FINAL

		F8:
			/*mov		eax, b
			push	eax*/
			call	dword ptr f8
			mov		[esp + 4], eax
			/*add		esp, 4*/
			jmp		FINAL

		F9:
			/*mov		eax, b
			push	eax*/
			mov		eax, [esp + 4]
			mov		ebx, [esp]
			mov		[esp], eax
			mov		[esp + 4], ebx
			
			call	dword ptr f9
		
			mov		eax, [esp + 4]
			mov		ebx, [esp]
			mov[esp], eax
			mov[esp + 4], ebx
			/*add		esp, 4*/
			jmp		FINAL

		F10:
			/*mov		eax, b
			push	eax*/
			mov		eax, [esp + 4]
			mov		ebx, [esp]
			mov[esp], eax
			mov[esp + 4], ebx

			call	dword ptr f10

			xor		eax, eax
			mov		[esp], eax

			mov		eax, [esp + 4]
			mov		ebx, [esp]
			mov[esp], eax
			mov[esp + 4], ebx
			/*add		esp, 4*/
			jmp		FINAL

		F11:
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
		
		F12:
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

		FINAL:

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

	EXIT:
		add		esp, 8
	}
}

/*void f(Matrix **a) {
	*a = create_matrix(3);
	//a->arr[0][0] = 45;
}*/

int main(void) {

	/*{
		//cout << "\n\nthird" << "\n";
		char
			*str1 = "Enter x:\n",
			*str2 = "Enter eps:\n",
			*fmt = "%lf",
			*ans = "answer = %lf\n";
		// tangent(x, eps);
		double x, eps, answer;
		__asm {
			//finit
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

			finit
			jmp		DEFAULT
			
		DEFAULT :
			sub		esp, 8
			fld		x
			fstp	qword ptr [esp]
			call	tangent
			add		esp, 8
			jmp		PRINT_ANSWER

		PRINT_ANSWER :
			
			sub		esp, 8
			fstp	qword ptr [esp]
			mov		eax, dword ptr ans
			push	eax
			call	printf
			add		esp, 12
		}
	}*/

	/*double x = 42.42;
	char *fmt = "%lf";
	int fsttmp;
	__asm {
		
		//finit

		lea		eax, x
		push	eax

		mov		eax, dword ptr fmt
		push	eax

		call	scanf_s

		//fstp	x

		//call	printf

		add		esp, 8
	
		finit

		fld		x
		fnstcw	fsttmp
		and		fsttmp, 1111001111111111b
		or fsttmp, 0000110000000000b // or []?
		//or		[fsttmp], 0C00h // устанавливаем RC = 11
		fldcw	fsttmp
		frndint 
		sub		esp, 8
		fstp	qword ptr[esp]

		mov		eax, dword ptr fmt
		push	eax

		call	printf
		add		esp, 12
		/*fnstcw	fsttmp
		and		fsttmp, 1111001111111111b
		or fsttmp, 0000000000000000b // очистка разрядов RC
		fldcw	fsttmp
		fld		my_pi // load PI
		fmulp	st(1), st(0) // = [x / PI] * PI
		fld		xx // load xx
		fsub	st(0), st(1) // st(0) = xx - [x / PI] * PI   
		fxch	st(1) // st(1) = xx - [x / PI] * PI   
		fstp	st(0) // delete st(0)
		// lea		eax, x*/
		// push	 eax
		//push	x
		

		/*sub		esp, 8
		fld		x
		fstp	qword ptr [esp]
		call	tangent
		add		esp, 8

		sub		esp, 8
		fstp	qword ptr[esp]

		mov		eax, dword ptr fmt
		push	eax

		call	printf
		add		esp, 12
	}*/

	//printf(fmt, x);

	int x = 0, y = 0, punkt = 0;
	
	vector<test_exercises::test_exercise *> tests = test_punkts();

	vector<string>	before = create_text_before(y),
		menu = create_menu();

	draw_before_and_menu(menu, before, x, y);
	char ch;

	SetConsoleTextAttribute(hConsole, selected);
	gotoxy(x, y);
	cout << PTR;
	draw_menu_punkt(punkt, menu, x, y);

	SetConsoleTextAttribute(hConsole, normal);

	int MOD = menu.size();

	bool condition = false;

	while (true) {
		ch = _getch();
		condition = break_cycle(ch, punkt, menu);
		if (condition) {
			break;
		}
		punkt_move(ch, MOD, menu, hConsole, x, y, punkt);
		do_punkt(ch, x, y, punkt, hConsole, tests, before, menu);
	}
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

	//const double eps = 1e-1;

	//for (double a = -M_PI; a < M_PI; a += eps) {
	//	double res = tangent(-atan(1));
	//	cout << "my_function = " << res << "\n";
	//	cout << "original_tan = " << tan(-atan(1)) << "\n";
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
	//return 0;
}