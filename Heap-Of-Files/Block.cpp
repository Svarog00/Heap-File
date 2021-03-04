#include <fstream>
#include <iostream>
#include "Block.h"

Block::Block()
{

}

void Block::AddStudent()
{
	//Enter data of a student
	_block.push_back(Student());
}

void Block::ChangeStudent(int index)
{
	//Find the index of the student in the vector
	//call setters
}

void Block::DeleteStudent(int index)
{
	//Find the index of the student in the vector
	//erase it from vector
}

void Block::FindStudent(int index)
{
	//Find the index of the student in the vector
	//Show info
}
