#include <iostream>

void func()
{
	setlocale(LC_ALL, "");
	std::cout << "\nПроверка с помощью С++:" << std::endl;
    int count;
	int k = 0;
	bool flag = false;
	for (int i = 1; i <= 127; i++){
		count = (i * i) - 1;
		for (int j = 2; j < count; j++){
			if (count % j == 0){
				flag = true;
				break;
			}
		}
		if (!flag){
			if ((i * i - 1) != 0) {
				k++;
				if (k == 200) {
					std::cout << "Двухсотое число это: " << i << std::endl;
					break;
				}
				std::cout << "Простое число это: " << i << std::endl;
			}
		}
		flag = false;
	}
	if (!flag) std::cout << "Двухсотого числа нет" << std::endl;
	std::cout << "Количество таких чисел: " << k << std::endl;
}

void print2(int x)
{
	setlocale(LC_ALL, "");
	std::cout << "Двухсотое число это: " << x << std::endl;
}

void printNO()
{
	setlocale(LC_ALL, "");
	std::cout << "Двухсотого числа нет" << std::endl;
}

void printK(int x)
{
	setlocale(LC_ALL, "");
	std::cout << "Количество таких чисел: " << x << std::endl;
}

int main()
{
	int count = 0;
	int yes = 0;
	int F = 0;
	_asm{
		xor edx, edx
		mov ecx, 1
		loop1:
		inc ecx
		mov eax, ecx
		mul eax
		dec eax
		mov ebx, eax
		cmp ecx, 127
		jg end
		push ecx
		mov ecx, 2
		cycle:
			mov eax, ebx
			div ecx
			cmp edx, 0
			jne next
			mov F, 1
			next:
			xor edx, edx
			inc ecx
			cmp ecx, ebx
		jl cycle
		cmp F, 1
		je skip
		inc count
		cmp count, 200
		jne skip
		add yes, 1
		push ebx
			call print2
		pop ebx
		skip:
		pop ecx
		jmp loop1
		end:
		cmp yes, 0
		jne no
		call printNO
		no:
		mov eax, count
		push eax
		call printK
		pop eax

	}
	func();
}
