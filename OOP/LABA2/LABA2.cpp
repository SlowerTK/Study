//Вариант 2
#include "Ярусский"
#include <iostream>
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
	street = name;
}

void MailAdress::SetHouseNumber(int number) {
	house = number;
}

void MailAdress::SetApartmentNumber(int number) {
	apartment = number;
}

void newMailAdress(MailAdress &Name) {
	char* newStreet = new char[100];
	int newHouse = NULL;
	int newApartment = NULL;

	std::cout << "Введите имя улицы: ";
	std::cin >> newStreet;
	std::cout << "Введите номер дома: ";
	std::cin >> newHouse;
	std::cout << "Введите номер квартиры: ";
	std::cin >> newApartment;

	Name.SetStreetName(newStreet);
	Name.SetHouseNumber(newHouse);
	Name.SetApartmentNumber(newApartment);
	delete[] newStreet;
}

void outMailAdress(MailAdress &Name) {
	std::cout << "Улица: " << Name.GetStreetName() << std::endl;
	std::cout << "Дом: " << Name.GetHouseNumber() << std::endl;
	std::cout << "Квартира: " << Name.GetApartmentNumber() << std::endl;
}

int main()
{
	Ярусский;
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
	system("pause");
	system("cls");

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