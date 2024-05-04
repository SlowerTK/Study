#include <iostream>
#include <fstream>


using namespace std;

void Input2TextFile(int i, double d, char c, char* s);
void Output4TextFile();

void Input2BinFile(int i, double d, char c, char* s);
void Output4BinFile();

int main() {
    setlocale(LC_ALL, "RUS");
    int choose = 0;
    int integer;
    double double_;
    char char_;
    char* string = new char[100];

    while (true) {
        choose = 0;
        cout << "Меню\n1)Ввести данные\n2)Вывести данные\n3)Выход" << endl;
        cin >> choose;
        switch (choose)
        {
        case 1:
            cout << "Введите целое число: ";
            cin >> integer;
            cout << "Введите вещественное число: ";
            cin >> double_;
            cout << "Введите символ: ";
            cin >> char_;
            cout << "Введите строку: ";
            fgets(string, 100, stdin);
            string[strcspn(string, "\n")] = NULL;

            choose = 0;

            cout << "Тип файла?\n1).txt\n2).bin" << endl;
            cin >> choose;
            switch (choose)
            {
            case 1:
                Input2TextFile(integer, double_, char_, string);
                break;
            case 2:
                Input2BinFile(integer, double_, char_, string);
                break;
            default:
                break;
            }
            break;
        case 2:
            choose = 0;

            cout << "Тип файла?\n1).txt\n2).bin" << endl;
            cin >> choose;
            switch (choose)
            {
            case 1:
                Output4TextFile();
                break;
            case 2:
                Output4BinFile();
                break;
            default:
                break;
            }
            break;
        case 3:
            cout << "Выхожу" << endl;
            return 0;

        default:
            break;
        }
    }
    delete[] string;
    return 0;
}

void Input2TextFile(int i, double d, char c, char* s) {
    ofstream fout;
    fout.open("textfile.txt");

    fout << i << endl;
    fout << d << endl;
    fout << c << endl;
    fout << s << endl;

    fout.close();
}

void Output4TextFile() {
    ifstream fin("textfile.txt");
    cout << "\n" << fin.rdbuf() << endl;
    fin.close();
}

void Input2BinFile(int i, double d, char c, char* s) {
    ofstream fout;
    fout.open("binfile.bin");
    fout.write((char*)&i, sizeof(int));
    fout.write((char*)&d, sizeof(double));
    fout.write(&c, sizeof(char));
    fout.write(s, 100);
    fout.close();
}

void Output4BinFile() {
    ifstream f;
    f.open("binfile.bin");
    int i = 0;
    double d = 0;
    char c = 0;
    char* s = new char[100];
    f.read((char*)&i, sizeof(int));
    f.read((char*)&d, sizeof(double));
    f.read(&c, sizeof(char));
    f.read(s, 100);
    cout << "\n" << i << endl;
    cout << d << endl;
    cout << c << endl;
    cout << s << endl;
    f.close();
    delete[] s;
}