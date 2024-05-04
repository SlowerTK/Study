// A - dword
// B - byte
// C - word
//Вычислить: D = (A / B) * C
//           E = (C ^ 2 / B) - A
///вводить желательно в 10ричной
#include <iostream>

int main() {

	int32_t A = 4000000; //0x7FFFFFFF
	int8_t B =  -125;
	int16_t C = 2000;

	int32_t D = 0;
	int32_t E = 0;
	_asm {
		xor eax, eax
		mov al, B
		cbw
		cwde
		mov ebx, A
		xchg eax, ebx
		xor edx, edx
		idiv ebx
		movzx ebx, C
		imul ebx
		mov D, eax
	}

	std::cout << std::dec << "DEC D:" << D << std::endl;
	std::cout << std::hex << "HEX D:" << D << std::endl;
	_asm {
		xor eax, eax
		xor edx, edx
		mov ax, C
		imul ax
		mov bx, ax
	    mov al, B
		cbw
		xchg bx, ax
		idiv bx
		cwde
		sub eax, A
		mov E, eax
	}
	std::cout << std::dec << "DEC E:" << E << std::endl;
	std::cout << std::hex << "HEX E:" << E << std::endl;

	return 0;
}
