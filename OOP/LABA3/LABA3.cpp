//Вариант 2
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <string>


class MailAdress
{
public:
	char* GetStreetName();
	int GetHouseNumber();
	int GetApartmentNumber();

	void SetStreetName(char* name);
	void SetHouseNumber(int number);
	void SetApartmentNumber(int number);
private:
	char* street = new char[100];
	int house = 0;
	int apartment = 0;
};

char* MailAdress::GetStreetName() {
	return this->street;
}

int MailAdress::GetHouseNumber() {
	return this->house;
}

int MailAdress::GetApartmentNumber() {
	return this->apartment;
}

void MailAdress::SetStreetName(char* name) {
	strcpy(street, name);
}

void MailAdress::SetHouseNumber(int number) {
	house = number;
}

void MailAdress::SetApartmentNumber(int number) {
	apartment = number;
}

void newMailAdress(MailAdress& Name) {
	char* newStreet = new char[100];
	int newHouse = NULL;
	int fHouse = 0;
	int newApartment = NULL;
	int fApartment = 0;

	while (true) {
		fseek(stdin, 0, SEEK_END);
		std::cout << "Введите имя улицы: ";
		fgets(newStreet, 100, stdin);
		newStreet[strcspn(newStreet, "\n")] = 0;
		Name.SetStreetName(newStreet);

		char* temp = strtok(newStreet, " ");
		int counter = 0;
		while (temp != NULL) {
			if (!strcmp(temp, "ул") && counter < 1) {
				fHouse = 1;
			}
			if (!strcmp(temp, "пр") && counter < 1) {
				fHouse = 2;
			}
			if (!strcmp(temp, "пер") && counter < 1) {
				fHouse = 3;
			}
			counter++;
			temp = strtok(NULL, " ");
		};
		if (fHouse != 0) break;
		else std::cout << "Вы ввели неверное название улицы" << std::endl;
	}

	delete[] newStreet;
	
	while (true) {
		std::cout << "Введите номер дома: ";
		std::cin >> newHouse;
		if (fHouse == 1 && (newHouse > 100 || newHouse < 1)) {
			std::cout << "номер дома на улице не может быть меньше 1 или больше 100" << std::endl;
		}
		else if (fHouse == 2 && (newHouse > 1000 || newHouse < 1)) {
			std::cout << "номер дома на проспекте не может быть меньше 1 или больше 1000" << std::endl;
		}
		else if (fHouse == 3 && (newHouse > 30 || newHouse < 1)) {
			std::cout << "номер дома в переулке не может быть меньше 1 или больше 30" << std::endl;
		}
		else break;
	}


	Name.SetHouseNumber(newHouse);


	std::cout << "Этот дом частный? (д/Н): ";
	char ch = 0;
	std::cin >> ch;
	switch (ch)
	{
	case 'д':
		Name.SetApartmentNumber(-1);
		break;
	default:
		std::cout << "Введите номер квартиры: ";
		std::cin >> newApartment;
		Name.SetApartmentNumber(newApartment);
		break;
	}
}

void outMailAdress(MailAdress& Name) {
	std::cout << "Улица: " << Name.GetStreetName() << std::endl;
	std::cout << "Дом: " << Name.GetHouseNumber() << std::endl;
	if (Name.GetApartmentNumber() < 0) {
		std::cout << "Частный дом" << std::endl;
	}
	else {
		std::cout << "Квартира: " << Name.GetApartmentNumber() << std::endl;
	}
}

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	MailAdress Oleg;
	MailAdress Anton;

	newMailAdress(Oleg);
	newMailAdress(Anton);

	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "Введённые данные" << std::endl;
	outMailAdress(Oleg);
	std::cout << std::endl;
	std::cout << std::endl;
	outMailAdress(Anton);
	return 0;
}