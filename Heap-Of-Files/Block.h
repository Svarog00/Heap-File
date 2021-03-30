#pragma once
#include <vector>
#include <fstream>
#include "StudentClass.h"

class Block
{
private:
	std::vector<Student*> _block;
	Block* nextBlock;
	static Block* EntryBlock;
	static int count;
	int num;


public:
	Block(bool init = true);

	void AddStudent();
	void ChangeStudent(int index);
	void DeleteStudent(int index);
	void DeleteLastElement();
	void ShowStudent(int index);
	void ShowBlock(int shift = 0);
	void LoadInFile();
	void LoadInFile(std::ofstream& ofstream);
	void LoadFromFile(int shift = 0);

	Student* CheckIndex(int index);
	Student* FindStudent(int index, int shift = 0);
	Student* FindLastStudent();
};