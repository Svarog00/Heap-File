#include <iostream>
#include "StudentClass.h"

Student::Student()
{
	this->index = 0;
	this->name = "Undefined";
	this->secondName = "Undefined";
	this->thirdName = "Undefined";
	this->groupIndex = 0;
	std::cout << "New student added\n";
}

Student::Student(int index, std::string name, std::string secondName, std::string thirdName, int groupIndex)
{
	this->index = index;
	this->name = name;
	this->secondName = secondName;
	this->thirdName = thirdName;
	this->groupIndex = groupIndex;
	std::cout << "New student added\n";
}

void Student::GetInfo()
{
	std::cout << "Index: " << this->index << std::endl
		<< "Name: " << this->name << std::endl
		<< "Second name: " << this->secondName << std::endl
		<< "Patronymic: " << this->thirdName << std::endl
		<< "Index of the group: " << this->groupIndex << std::endl;
}

void Student::SetName(std::string newName)
{
	this->name = newName;
}

void Student::SetSecondName(std::string newName)
{
	this->secondName = newName;
}

void Student::SetThirdName(std::string newName)
{
	this->thirdName = newName;
}

void Student::SetIndex(int newIndex)
{
	this->index = newIndex;
}

void Student::SetGroupIndex(int newIndex)
{
	this->groupIndex = newIndex;
}
