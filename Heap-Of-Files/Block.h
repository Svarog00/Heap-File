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


public:
	Block(bool init = true);

	void AddStudent();
	void ChangeStudent(int index);
	void DeleteStudent(int index);
	void DeleteLastElement();
	void ShowStudent(int index);
	void ShowBlock();
	void LoadInFile();
	void LoadInFile(std::ofstream& ofstream);
	void LoadFromFile();
	void LoadFromFile(std::ifstream& ifstream);

	Student* CheckIndex(int index);
	Student* FindStudent(int index);
	Student* FindLastStudent();

	friend std::ostream& operator<<(std::ostream& os, const Block& block);
	friend std::istream& operator>>(std::istream& is, Block& block);
};