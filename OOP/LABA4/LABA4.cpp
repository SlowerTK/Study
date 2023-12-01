//Вариант 2
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <string>
#define NO_VALUE		-1

class MailAddress
{
public:
	char* GetStreetName();
	int GetHouseNumber();
	int GetApartmentNumber();

	void SetStreetName(char* name);
	void SetHouseNumber(int number);
	void SetApartmentNumber(int number);
private:
	char* street = new char[100] {"ул Ленина"};
	int house = 1;
	int apartment = 1;

	int type = 1;
};
class GalacticAddress: public MailAddress
{
public:
	void SetTailNumber(int number);
	void SetPlanetNumber(int number);
	void SetSatelliteNumber(int number);

	int GetTailNumber();
	int GetPlanetNumber();
	int GetSatelliteNumber();

private:
	int tail = 1;
	int planet = 1;
	int satellite = 1;
};

char* MailAddress::GetStreetName() {
	return this->street;
}
int MailAddress::GetHouseNumber() {
	return this->house;
}
int MailAddress::GetApartmentNumber() {
	return this->apartment;
}
void MailAddress::SetStreetName(char* name) {
	int fHouse = 0;
	char* temp = new char[100] {};
	strcpy(temp, name);
	temp = strtok(temp, " ");
	int counter = 0;
	if ((!strcmp(temp, "ул") || !strcmp(temp, "ул.")) && counter < 1) {
		fHouse = 1;
	}
	else if ((!strcmp(temp, "пр") || !strcmp(temp, "пр.")) && counter < 1) {
		fHouse = 2;
	}
	else if ((!strcmp(temp, "пер") || !strcmp(temp, "пер.")) && counter < 1) {
		fHouse = 3;
	}
	
	if (fHouse) {
		strcpy(street, name);
		type = fHouse;
	}
	else std::cout << "Введено неверное название улицы\n\tбудет установленно значение по умолчанию" << std::endl;
	delete[] temp;
}
void MailAddress::SetHouseNumber(int number) {

	if (type == 1 && (number > 100 || number < 1)) {
		std::cout << "Номер дома на улице не может быть меньше 1 или больше 100\n\tбудет установленно ближайшее значение" << std::endl;
		if (number > 100) number = 100;
		else number = 1;
	}
	else if (type == 2 && (number > 1000 || number < 1)) {
		std::cout << "Номер дома на проспекте не может быть меньше 1 или больше 1000\n\tбудет установленно ближайшее значение" << std::endl;
		if (number > 1000) number = 1000;
		else number = 1;
	}
	else if (type == 3 && (number > 30 || number < 1)) {
		std::cout << "Номер дома в переулке не может быть меньше 1 или больше 30\n\tбудет установленно ближайшее значение" << std::endl;
		if (number > 30) number = 30;
		else number = 1;
	}

	house = number;
}
void MailAddress::SetApartmentNumber(int number) {
	if (number < 1 && number != NO_VALUE) {
		std::cout << "Введено не верное значение квартиры\nБудет установленно значение по умолчанию" << std::endl;
		number = 1;
	}

	apartment = number;
}

void GalacticAddress::SetTailNumber(int number) {
	if (number < 1 || number > 6) {
		std::cout << "Введено не верное значение хвоста\n\tбудет установленно ближайшее значение" << std::endl;
		if (number > 6) number = 6;
		else number = 1;
	}

	tail = number;
}
void GalacticAddress::SetPlanetNumber(int number) {
	if (number < 1 || number > 10) {
		std::cout << "Введено не верное значение планеты\n\tбудет установленно ближайшее значение" << std::endl;
		if (number > 10) number = 10;
		else number = 1;
	}

	planet = number;
}
void GalacticAddress::SetSatelliteNumber(int number) {
	if (!((number > 1 && number < 70) || number == -1)){
		std::cout << "Введено не верное значение спутника\n\tбудет установленно ближайшее значение" << std::endl;
		if (number > 70) number = 70;
		else number = 1;
	}

	satellite = number;
}
int GalacticAddress::GetTailNumber() {
	return this->tail;
}
int GalacticAddress::GetPlanetNumber() {
	return this->planet;
}
int GalacticAddress::GetSatelliteNumber() {
	return this->satellite;
}

void setLocale() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
}
void newMailAddress(MailAddress& Name) {
	char* newStreet = new char[100];
	int newHouse = NULL;
	int newApartment = NULL;
	
	fseek(stdin, 0, SEEK_END);
	std::cout << "Введите имя улицы: ";
	fgets(newStreet, 100, stdin);
	newStreet[strcspn(newStreet, "\n")] = 0;
	Name.SetStreetName(newStreet);

	delete[] newStreet;

	std::cout << "Введите номер дома: ";
	std::cin >> newHouse;
	Name.SetHouseNumber(newHouse);

	std::cout << "Этот дом частный? (д/Н): ";
	char ch = 0;
	std::cin >> ch;
	if (ch == 'д')
		newApartment = NO_VALUE;
	else{
		std::cout << "Введите номер квартиры: ";
		std::cin >> newApartment;
	}
	Name.SetApartmentNumber(newApartment);
}
void outMailAddress(MailAddress& Name) {
	std::cout << "Улица: " << Name.GetStreetName() << std::endl;
	std::cout << "Дом: " << Name.GetHouseNumber() << std::endl;
	if (Name.GetApartmentNumber() != NO_VALUE) {
		std::cout << "Квартира: " << Name.GetApartmentNumber() << std::endl; 
	}
	else {
		std::cout << "Частный дом" << std::endl;
	}
}
void newGalacticAddress(GalacticAddress& Name) {
	int newTail = 0;
	int newPlanet = 0;
	int newSatellite = 0;
	
	std::cout << "Введите номер хвоста(от 1 до 6)" << std::endl;
	std::cin >> newTail;
	Name.SetTailNumber(newTail);
		
	std::cout << "Введите номер планеты(от 1 до 10)" << std::endl;
	std::cin >> newPlanet;
	Name.SetPlanetNumber(newPlanet);

	std::cout << "Нужно указать номер спутника?(д/Н): ";
	char ch = 0;
	std::cin >> ch;
	if (ch == 'д') {
		std::cout << "Введите номер спутника(от 1 до 70)" << std::endl;
		std::cin >> newSatellite;
	}
	else
		newSatellite = NO_VALUE;
	Name.SetSatelliteNumber(newSatellite);
}
void outGalacticAddress(GalacticAddress& Name) {
	std::cout << "Хвост: " << Name.GetTailNumber() << std::endl;
	std::cout << "Планета: " << Name.GetPlanetNumber() << std::endl;
	if(Name.GetSatelliteNumber() != NO_VALUE)
		std::cout << "Спутник: " << Name.GetSatelliteNumber() << std::endl;
}
bool InputAddress(GalacticAddress& Name) {
	std::cout << "Указать \033[4mполный\033[24m адресс?(д/Н): ";
	char ch = 0;
	std::cin >> ch;
	bool FullAddress = false;
	if (ch == 'д') {
		newGalacticAddress(Name);
		FullAddress = true;
	}
	newMailAddress(Name);
	return FullAddress;
}
void OutputAddress(GalacticAddress& Name, bool FullAddress) {
	if (FullAddress == true) outGalacticAddress(Name);
	outMailAddress(Name);
}

int main()
{
	setLocale();
	GalacticAddress Oleg;
	GalacticAddress Anton;
	bool FullAddressO = false;
	bool FullAddressA = false;
	FullAddressO = InputAddress(Oleg);
	FullAddressA = InputAddress(Anton);

	//char* copy = new char[100] {};
	//strcpy(copy, "пер. Вишневая");
	//Oleg.SetStreetName(copy);
	//delete[](copy);
	//OutputAddress(Oleg, FullAddressO);
	//Oleg.SetHouseNumber(101);

	std::cout << "\n\n" << "Введённые данные" << std::endl;
	outGalacticAddress(Oleg);
	OutputAddress(Oleg, FullAddressO);
	std::cout << "\n" << std::endl;
	OutputAddress(Anton, FullAddressA);
	return 0;
}