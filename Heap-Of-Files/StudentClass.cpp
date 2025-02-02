#include <iostream>
#include <fstream>
#include "StudentClass.h"

Student::Student()
{
	char tmp[] = "Undefined";
	this->index = -1;
	memcpy(nam, tmp, sizeof(tmp));
	memcpy(secName, tmp, sizeof(tmp));
	memcpy(thName, tmp, sizeof(tmp));
	this->groupIndex = -1;
}

Student::Student(int index, char name[], char secondName[], char thirdName[], int groupIndex)
{
	this->index = index;
	memcpy(nam, name, 64);
	memcpy(secName, secondName, 64);
	memcpy(thName, thirdName, 64);
	this->groupIndex = groupIndex;
	std::cout << "New student added\n";
}

void Student::GetInfo()
{
	std::cout << "Index: " << this->index << std::endl
		<< "Name: " << this->nam << std::endl
		<< "Second name: " << this->secName << std::endl
		<< "Patronymic: " << this->thName << std::endl
		<< "Index of the group: " << this->groupIndex << std::endl;
	std::cout << "\n==============================================\n";
}
//Setters
void Student::SetName(std::string newName)
{
	memcpy(nam, newName.c_str(), sizeof(newName));
}

void Student::SetSecondName(std::string newName)
{
	memcpy(secName, newName.c_str(), sizeof(newName));
}

void Student::SetThirdName(std::string newName)
{
	memcpy(thName, newName.c_str(), sizeof(newName));
}

void Student::SetIndex(int newIndex)
{
	this->index = newIndex;
}

void Student::SetGroupIndex(int newIndex)
{
	this->groupIndex = newIndex;
}
//Getters
int Student::GetIndex()
{
	return index;
}

char* Student::GetSecName()
{
	return secName;
}

char* Student::GetThName()
{
	return thName;
}

char* Student::GetN()
{
	return nam;
}

int Student::GetGroupIndex()
{
	return groupIndex;
}
