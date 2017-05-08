// Copyright (c) 2017 Denis Skripov
// https://github.com/nizhikebinesi/labs_inline_assembler
#include "first_exercise.h"

namespace exercises {
	// Exercise:
	// Определить   номер   позиции,  с  которой  начинается   первое   слева
	// вхождение указанной строки символов.
	int index_of(char* src, char* tgt) {
		//int src_length, tgt_length;
		//bool condition;
		__asm {
			mov		eax, src
			cmp		byte ptr[eax], 0
			je		SRC_ZERO_LENGTH

			mov		edx, tgt
			cmp		byte ptr[edx], 0
			je		TGT_ZERO_LENGTH

			xor		ecx, ecx
			COUNTING_TGT_LENGTH :
			cmp		byte ptr[edx], 0
				je		NEXT_TGT_LENGTH
				inc		edx
				inc		ecx
				jmp COUNTING_TGT_LENGTH
				NEXT_TGT_LENGTH :
			cmp		ecx, 0
				jle		TGT_ZERO_LENGTH
				push	ecx
				;//mov		tgt_length, ecx

			mov		ebx, src
				xor		ecx, ecx
				COUNTING_SRC_LENGTH :
			cmp		byte ptr[ebx], 0
				je		NEXT_SRC_LENGTH
				inc		ebx
				inc		ecx
				jmp		COUNTING_SRC_LENGTH
				NEXT_SRC_LENGTH :
			cmp		ecx, 0
				jle		SRC_ZERO_LENGTH
				;//mov		src_length, ecx


			mov		esi, ecx
				pop		edi
				;//mov		edi, tgt_length
			sub		esi, edi
				cmp		esi, 0
				jl		DIFFERENCE_BETWEEN_LENGTHES_LESS_THEN_ZERO

				;// esi = src_length - tgt_length

			xor		ecx, ecx
				xor		edi, edi
				FOR_I :
			mov		ebx, src
				mov		edx, tgt
				cmp		byte ptr[ebx][ecx], 0
				je		END_FOR_I
				or edi, 1
				FOR_J :
				cmp		byte ptr[edx], 0
				je		NEXT_I
				mov		al, byte ptr[edx]
				cmp[ebx][ecx], al;//byte ptr [ebx][ecx], byte ptr [edx]
			je		EQUAL
				and		edi, 0
				jmp		NEXT_I
				EQUAL :
			inc		ebx
				inc		edx
				jmp		FOR_J
				NEXT_I :
			cmp		edi, 1
				je		HAS_SUBSTR
				inc		ecx
				jmp		FOR_I

				END_FOR_I :
		SRC_ZERO_LENGTH:
		TGT_ZERO_LENGTH:
		DIFFERENCE_BETWEEN_LENGTHES_LESS_THEN_ZERO:
			mov		eax, -1
				jmp		FINAL
				;//SRC_ZERO_LENGTH:
			;//	mov		eax, -1
			;//	jmp		FINAL
			;//TGT_ZERO_LENGTH:
			;//	mov		eax, -1
			;//	jmp		FINAL
			;//DIFFERENCE_BETWEEN_LENGTHES_LESS_THEN_ZERO:
			;//	mov		eax, -1
			;//	jmp		FINAL
		HAS_SUBSTR:
			mov		eax, ecx
				jmp FINAL
				FINAL :
		}
		// return value in eax, it is convenion of Visual Studio
	}

	std::vector<int> prefix_function(std::string s) {
		int n = (int)s.length();
		std::vector<int> pi(n);
		for (int i = 1; i<n; ++i) {
			int j = pi[i - 1];
			while (j > 0 && s[i] != s[j])
				j = pi[j - 1];
			if (s[i] == s[j])  ++j;
			pi[i] = j;
		}
		return pi;
	}

	int index_of_pratt(std::string src, std::string tgt) {
		if (src.length() == 0 || tgt.length() == 0) {
			return -1;
		}
		std::vector<int> pr = prefix_function(tgt + "#" + src);
		for (int i = 0; i < pr.size(); i++) {
			if (pr[i] == tgt.length()) {
				return i - 2 * tgt.length();
			}
		}
		return -1;
	}
}