#pragma once
#include <vector>
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
	Student* CheckIndex(int index);
	Student* FindStudent(int index);
};