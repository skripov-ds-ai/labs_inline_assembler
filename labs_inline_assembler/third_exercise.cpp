// Copyright (c) 2017 Denis Skripov
// https://github.com/nizhikebinesi/labs_inline_assembler
#include "third_exercise.h"

namespace exercises {
	double tangent(double x, double epsilon) {
		const int m = 15, n = 2, k = 3;
		const double right = M_PI_2;

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
				
		CALCULATE :

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
	}
}