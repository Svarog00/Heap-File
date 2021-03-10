#pragma once
#include <vector>
#include <fstream>
#include "StudentClass.h"

class Block
{
private:
	std::vector<Student> _block;
	Block* nextBlock;

public:
	Block();

	void AddStudent();
	void ChangeStudent(int index);
	void DeleteStudent(int index);
	void ShowStudent(int index);
	void ShowBlock();
	void LoadInFile();
	void LoadInFile(std::ofstream& ofstream);
	void LoadFromFile();
	void LoadFromFile(std::ifstream& ifstream);
	Student* CheckIndex(int index);
	Student* FindStudent(int index);
};