//2) Даны две переменные A и B.Переставить байты в переменных по следующей схеме :
//Начальная нумерация байт
//A = 11 22 33 44
//B = 55 66 77 88
//После перестановки
//A = 22 11 44 88
//B = 55 66 77 33
#include "Ярусский"
#include <Windows.h>

int main() {
    Ярусский;
    
    long int A = 0x11223344;
    long int B = 0x55667788;
    unsigned long long int timemin = 10000001;
    unsigned long long int time1 = 0;
    unsigned long long int time2 = 0;
    for (int i = 0; i < 10; i++) {
        A = 0x11223344;
        B = 0x55667788;
        //printf("Начальная нумерация байт:\nA=%0X\nB=%0X\n\n", A, B);
        time1 = 0;
        time2 = 0;
        _asm {
            RDTSC
            mov dword ptr time1, eax
            mov dword ptr time1[4], edx
            mov ebx, A
            mov edx, B

            mov eax, edx
            xchg al, bh
            rol bx, 8
            rol ebx, 16
            rol bx, 8
            rol ebx, 16

            mov A, ebx
            mov B, eax
            RDTSC
            mov dword ptr time2, eax
            mov dword ptr time2[4], edx
        }
        if (time2 - time1 < timemin) {
            timemin = time2 - time1;
            std::cout << std::dec << "TIMEmin:" << timemin << std::endl;
        }
            Sleep(251);
    }
    //printf("После перестановки:\nA=%0X\nB=%0X\n\n", A, B);
    //std::cout << std::dec << "TIMEmin:" << timemin << std::endl;
    return 0;
}
