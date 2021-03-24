#pragma once
#include <string>
#include <iostream>

class Student
{
private:
	int index;
	std::string secondName;
	std::string name;
	std::string thirdName;
	int groupIndex;

public:
	Student();
	Student(int index, std::string name, std::string secondName, std::string thirdName, int groupIndex);

	void GetInfo();
	void SetName(std::string newName);
	void SetSecondName(std::string newName);
	void SetThirdName(std::string newName);
	void SetIndex(int newIndex);
	void SetGroupIndex(int newIndex);

	int GetIndex();
	std::string GetSecondName();
	std::string GetName();
	std::string GetThirdName();
	int GetGroupIndex();

	friend std::ostream& operator<<(std::ostream& os, const Student& stud);
	friend std::istream& operator>>(std::istream& is, Student& stud);
};