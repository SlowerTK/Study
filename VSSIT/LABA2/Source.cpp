//2) ���� ��� ���������� A � B.����������� ����� � ���������� �� ��������� ����� :
//��������� ��������� ����
//A = 11 22 33 44
//B = 55 66 77 88
//����� ������������
//A = 22 11 44 88
//B = 55 66 77 33
#include "��������"

int main() {
    ��������;

    long int A = 0x11223344;
    long int B = 0x55667788;

    printf("��������� ��������� ����:\nA=%0X\nB=%0X\n\n", A, B);

    _asm {
        mov ebx, A
        mov edx, B

        mov eax, edx
        xchg al, bh

        xchg bh, bl
        
        
        
        rol ebx, 16
        rol bx, 8
        rol ebx, 16

        

        mov A, ebx
        mov B, eax
    }
    printf("����� ������������:\nA=%0X\nB=%0X\n\n", A, B);

    return 0;
}
