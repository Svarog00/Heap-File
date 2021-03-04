#pragma once
#include <vector>
#include "StudentClass.h"

class Block
{
private:
	std::vector<Student> _block;
	int curNum;

public:
	Block();

	void AddStudent();
	void ChangeStudent(int index);
	void DeleteStudent(int index);
	void FindStudent(int index);
};