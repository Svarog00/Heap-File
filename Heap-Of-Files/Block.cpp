#include <fstream>
#include <iostream>
#include "Block.h"

Block* Block::EntryBlock = nullptr;

Block::Block(bool init)
{
	nextBlock = nullptr;
	if (init)
	{
		LoadFromFile();
		EntryBlock = this;
	}
}

void Block::AddStudent()
{
	if (_block.size() == 5)
	{
		if (nextBlock != nullptr)
			nextBlock->AddStudent();
		else
		{
			nextBlock = new Block(false);
			std::cout << "--------------------------Added new block\n";
			nextBlock->AddStudent();
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

		_block.push_back(new Student(index, name, secondName, thirdName, groupIndex));
		LoadInFile();
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
			LoadInFile();
			break;
		}
		case 2:
		{
			std::string newName;
			std::cout << "New second name: \n";
			std::cin >> newName;
			student->SetSecondName(newName);
			LoadInFile();
			break;
		}
		case 3:
		{
			std::string newName;
			std::cout << "New third name: \n";
			std::cin >> newName;
			student->SetThirdName(newName);
			LoadInFile();
			break;
		}
		case 4:
		{
			int newGroupIndex;
			std::cout << "New group index: \n";
			std::cin >> newGroupIndex;
			student->SetGroupIndex(newGroupIndex);
			LoadInFile();
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
			if (_block[i]->GetIndex() == index)
			{
				_block[i]->~Student();
				_block[i] = this->FindLastStudent();
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
		LoadInFile();
	}
}

void Block::ShowStudent(int index)
{
	//Find student by index and show info
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
			_block[i]->GetInfo();
			if (i == 4 && nextBlock != nullptr)
			{
				nextBlock->ShowBlock();
			}
		}
	}
}

void Block::LoadInFile()
{
	std::ofstream outf("Block.bin", std::ios::binary);
	if (outf)
	{
		for (auto student : _block)
		{
			outf << *student;
			outf << " ";
		}
		//if(nextBlock != nullptr) nextBlock->LoadInFile(outf);
		std::cout << "Block has been loaded in file!\n";
	}
	else std::cout << "Couldn't open file for writing!\n";
	outf.close();
}

void Block::LoadInFile(std::ofstream& ofstream)
{
	if (ofstream)
	{
		for (auto student : _block)
		{
			ofstream << *student;
			ofstream << " ";
		}
		if (nextBlock != nullptr)
			nextBlock->LoadInFile(ofstream);
	}
}

void Block::LoadFromFile()
{
	std::ifstream ifs("Block.bin");
	if (ifs)
	{
		while (!ifs.eof())
		{
			Student* tmp = new Student();
			ifs >> *tmp;
			if (ifs.eof())
			{
				break;
			}
			_block.push_back(tmp);
			if (this->_block.size() == 5 && nextBlock != nullptr)
			{
				nextBlock->LoadFromFile(ifs);
				break;
			}
			else if (this->_block.size() == 5 && nextBlock == nullptr)
			{
				nextBlock = new Block();
				nextBlock->LoadFromFile(ifs);
				break;
			}
		}
	}
	else std::cout << "Couldn't open file for writing!\n";
}

void Block::LoadFromFile(std::ifstream& ifstream)
{
	if (ifstream)
	{
		while (!ifstream.eof())
		{
			Student* tmp = new Student();
			ifstream >> *tmp;
			if (ifstream.eof())
			{
				break;
			}
			_block.push_back(tmp);
			if (this->_block.size() == 5 && nextBlock != nullptr)
			{
				nextBlock->LoadFromFile(ifstream);
				break;
			}
			else if (this->_block.size() == 5 && nextBlock == nullptr)
			{
				nextBlock = new Block();
				nextBlock->LoadFromFile(ifstream);
				break;
			}
		}
	}
}

Student* Block::CheckIndex(int index)
{
	return EntryBlock->FindStudent(index);
}

Student* Block::FindStudent(int index)
{
	//Find the student by index in the vector 
	//Return pointer on the student
	if (_block.size() > 0)
	{
		for (size_t i = 0; i < _block.size(); i++)
		{
			if (_block[i]->GetIndex() == index)
			{
				return _block[i];
			}
			if (i == 4 && nextBlock != nullptr)
			{
				return nextBlock->FindStudent(index);
			}
		}
	}
	return nullptr;
}

Student* Block::FindLastStudent()
{
	if (_block.size() == 5 && nextBlock != nullptr)
	{
		return nextBlock->FindLastStudent();
	}
	else if (_block.size() <= 5 && nextBlock == nullptr)
	{
		if (_block[_block.size() - 1] == nullptr)
		{
			return nullptr;
		}
		return _block[_block.size() - 1];
	}
	else return nullptr;
}

