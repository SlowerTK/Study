#include <iostream>
#include <fstream>


using namespace std; 

void Input2TextFile(int i, double d, char c, char* s);
void Output4TextFile();

void Input2BinFile(int i, double d, char c, char* s);
void Output4BinFile();

int main(){
    int choose = 0;
    int cel;
    double ves;
    char sim;
    char* str = new char[100];

    while(true){
        choose = 0;
        cout << "Меню\n1)Ввести данные\n2)Вывести данные\n3)Выход" << endl;
        cin >> choose;
        switch (choose)
        {
        case 1:
            cout << "Введите целое число: ";
            cin >> cel;
            cout << "Введите вещественное число: ";
            cin >> ves;
            cout << "Введите символ: ";
            cin >> sim;
            cout << "Введите строку: ";
            cin >> str;

            choose = 0;
            
            cout << "Тип файла?\n1).txt\n2).bin\n3)в оба" << endl;
            cin >> choose;
            switch (choose)
            {
            case 1:
                Input2TextFile(cel, ves, sim, str);
                break;
            case 2:
                Input2BinFile(cel, ves, sim, str);
                break;
            case 3:
                Input2TextFile(cel, ves, sim, str);
                Input2BinFile(cel, ves, sim, str);
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
    delete [] str;
    return 0;
}

void Input2TextFile(int i, double d, char c, char* s){
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

void Input2BinFile(int i, double d, char c, char* s){
    ofstream fout;
    fout.open("binfile.bin");
    fout.write((char*) &i, sizeof(int));
    fout.write((char*) &d, sizeof(double));
    fout.write((char*) &c, sizeof(char));
    fout.write((char*) &s, sizeof(char*));
    fout.close();

}

void Output4BinFile(){
    ifstream f;
    f.open("binfile.bin");
    int i;
    double d;
    char c;
    char* s = new char[100];
    f.read((char*) &i, sizeof(int));
    f.read((char*) &d, sizeof(double));
    f.read((char*) &c, sizeof(char));
    f.read((char*) &s, sizeof(char*));
    cout << "\n" << i << endl;
    cout << d << endl;
    cout << c << endl;
    cout << s << endl;
    f.close();
    delete [] s;
}