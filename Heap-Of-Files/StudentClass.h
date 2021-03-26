#pragma once
#include <string>
#include <iostream>

class Student
{
private:
	int index;
	int groupIndex;

	char secName[64];
	char nam[64];
	char thName[64];

public:
	Student();
	Student(int index, char name[], char secondName[], char thirdName[], int groupIndex);

	void GetInfo();
	void SetName(std::string newName);
	void SetSecondName(std::string newName);
	void SetThirdName(std::string newName);
	void SetIndex(int newIndex);
	void SetGroupIndex(int newIndex);
	void Load();

	int GetIndex();
	int GetGroupIndex();

	char* GetSecName();
	char* GetN();
	char* GetThName();

	friend std::ostream& operator<<(std::ostream& os, const Student& stud);
	friend std::istream& operator>>(std::istream& is, Student& stud);
};