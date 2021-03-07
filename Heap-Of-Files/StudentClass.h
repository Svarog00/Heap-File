#pragma once
#include <string>

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
};