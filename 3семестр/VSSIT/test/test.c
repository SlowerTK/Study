//7) На промежутке от - 128 до 127. Подсчитать количество таких пар чисел
//Х и У, что 50 < (Х - У) <= 80. Ответ вывести на экран.

#include <stdlib.h>
#include <stdio.h>

void func() {
	int k = 0;
	for (int i = 127; i >= -128; i--) {
		for (int j = 127; j >= -128; j--) {
			if (50 < (i - j) && (i - j) <= 80) {
				k++;
			}
		}
	}
	printf("%d ", k);
}

int main()
{

	func();
}
