//������� 2
#define _CRT_SECURE_NO_WARNINGS
#include "��������"
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
	strcpy(street,name);
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
	int newApartment = NULL;

	std::cout << "������� ��� �����: ";
	std::cin >> newStreet;
	std::cout << "������� ����� ����: ";
	std::cin >> newHouse;
	std::cout << "������� ����� ��������: ";
	std::cin >> newApartment;

	Name.SetStreetName(newStreet);
	Name.SetHouseNumber(newHouse);
	Name.SetApartmentNumber(newApartment);
	delete[] newStreet;
}

void outMailAdress(MailAdress &Name) {
	std::cout << "�����: " << Name.GetStreetName() << std::endl;
	std::cout << "���: " << Name.GetHouseNumber() << std::endl;
	std::cout << "��������: " << Name.GetApartmentNumber() << std::endl;
}

int main()
{
	��������;
	MailAdress Oleg;
	MailAdress Anton;

	newMailAdress(Oleg);
	newMailAdress(Anton);

	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "�������� ������" << std::endl;
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

	std::cout << "�������� ������" << std::endl;
	outMailAdress(Oleg);
	std::cout << std::endl;
	std::cout << std::endl;
	outMailAdress(Anton);
	return 0;
}