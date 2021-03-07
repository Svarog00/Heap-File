#include <fstream>
#include <iostream>
#include "Block.h"

Block::Block()
{
	nextBlock = nullptr;
}

void Block::AddStudent()
{
	if (_block.size() == 5)
	{
		if (nextBlock != nullptr)
			nextBlock->AddStudent();
		else
		{
			nextBlock = new Block();
			nextBlock->AddStudent();
			std::cout << "--------------------------Added new block\n";
		}
	}
	else
	{
		int index;
		std::string secondName;
		std::string name;
		std::string thirdName;
		int groupIndex;

		//Enter data of a student
		std::cout << "Index: ";
		std::cin >> index;
		Student* tmp = CheckIndex(index);
		while (tmp != nullptr)
		{
			std::cout << "This index is occupied. Enter another index.\n";
			std::cin >> index;
			tmp = CheckIndex(index);
		}

		std::cout << "\nSecond name: ";
		std::cin >> secondName;
		std::cout << "\nName: ";
		std::cin >> name;
		std::cout << "\nThird name: ";
		std::cin >> thirdName;
		std::cout << "\nGroup index: ";
		std::cin >> groupIndex;

		_block.push_back(Student(index, name, secondName, thirdName, groupIndex));
	}
}

void Block::ChangeStudent(int index)
{
	//Find the index of the student in the vector
	//call setter
	Student* student = FindStudent(index);
	if (student == nullptr)
		std::cout << "There is no such student\n";
	else
	{
		int key;
		std::cout << "What you want to change?\n"
			<< "1 - Name\n"
			<< "2 - Second name\n"
			<< "3 - Third name\n"
			<< "4 - Group index\n";
		std::cin >> key;
		switch (key)
		{
		case 1:
		{
			std::string newName;
			std::cout << "New name: \n";
			std::cin >> newName;
			student->SetName(newName);
			break;
		}
		case 2:
		{
			std::string newName;
			std::cout << "New second name: \n";
			std::cin >> newName;
			student->SetSecondName(newName);
			break;
		}
		case 3:
		{
			std::string newName;
			std::cout << "New third name: \n";
			std::cin >> newName;
			student->SetThirdName(newName);
			break;
		}
		case 4:
		{
			int newGroupIndex;
			std::cout << "New group index: \n";
			std::cin >> newGroupIndex;
			student->SetGroupIndex(newGroupIndex);
			break;
		}
		default:
			std::cout << "Wrong command\n";
			break;
		}
	}
}

void Block::DeleteStudent(int index)
{
	//Find the index of the student in the vector
	//erase it from vector
	if (_block.size() > 0)
	{
		for (size_t i = 0; i < _block.size(); i++)
		{
			if (_block[i].GetIndex() == index)
			{
				_block.erase(_block.begin()+i);
				break;
			}
			else if (i == 4 && nextBlock != nullptr)
			{
				nextBlock->DeleteStudent(index);
			}
			else if(i == 4 && nextBlock == nullptr)
			{
				std::cout << "There is no such student\n";
			}
		}
	}
}

void Block::ShowStudent(int index)
{
	Student* student = FindStudent(index);
	if (student == nullptr)
		std::cout << "There is no such student\n";
	else 
		student->GetInfo();
}

void Block::ShowBlock()
{
	if (_block.size() > 0)
	{
		for (size_t i = 0; i < _block.size(); i++)
		{
			_block[i].GetInfo();
			if (i == 4 && nextBlock != nullptr)
			{
				nextBlock->ShowBlock();
			}
		}
	}
}

Student* Block::CheckIndex(int index)
{
	return FindStudent(index);
}

Student* Block::FindStudent(int index)
{
	//Find the index of the student in the vector 
	//Show info
	if (_block.size() > 0)
	{
		for (size_t i = 0; i < _block.size(); i++)
		{
			if (_block[i].GetIndex() == index)
			{
				return &_block[i];
			}
			if (i == 4 && nextBlock != nullptr)
			{
				nextBlock->FindStudent(index);
			}
		}
	}
	return nullptr;
}

