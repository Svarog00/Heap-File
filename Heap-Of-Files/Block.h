#pragma once
#include <fstream>
#include "StudentClass.h"
#include "FileManager.h"

struct Container
{
	Student block[5];
public:
	Container();
};

class Block
{
public:
	Container _block;
private:
	static Block* EntryBlock;
	FileManager fileManager;
	static int num;
	int shift;

public:
	Block(bool init = true);

	void AddStudent();
	void ChangeStudent(int index);
	void DeleteStudent(int index);
	void ShowStudent(int index);
	void ShowBlock();
	void Exit();

	Student* CheckIndex(int index);
	Student* FindStudent(int index);
};