#include <fstream>
#include <iostream>
#include "Block.h"

Block* Block::EntryBlock = nullptr;
int Block::count = 0;

//������: �������� ��������, ��������� ���������� � ��������

Block::Block(bool init)
{
	nextBlock = nullptr;
	num = count;
	count++;
	if (init)
	{
		//LoadFromFile();
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
			std::cout << "--------------------------Added new block" << std::endl;
			nextBlock->AddStudent();
		}
	}
	else
	{
		int index;
		char secondName[64];
		char name[64];
		char thirdName[64];
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
		
		std::ofstream outf("Block.bin", std::ios::binary | std::ios::app);
		outf.write((char*)new Student(index, name, secondName, thirdName, groupIndex), sizeof(Student));

		/*_block.push_back(new Student(index, name, secondName, thirdName, groupIndex));
		EntryBlock->LoadInFile();*/
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
			EntryBlock->LoadInFile();
			break;
		}
		case 2:
		{
			std::string newName;
			std::cout << "New second name: \n";
			std::cin >> newName;
			student->SetSecondName(newName);
			EntryBlock->LoadInFile();
			break;
		}
		case 3:
		{
			std::string newName;
			std::cout << "New third name: \n";
			std::cin >> newName;
			student->SetThirdName(newName);
			EntryBlock->LoadInFile();
			break;
		}
		case 4:
		{
			int newGroupIndex;
			std::cout << "New group index: \n";
			std::cin >> newGroupIndex;
			student->SetGroupIndex(newGroupIndex);
			EntryBlock->LoadInFile();
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
	LoadFromFile();
	if (_block.size() > 0)
	{
		for (size_t i = 0; i < _block.size(); i++)
		{
			if (_block[i]->GetIndex() == index)
			{
				Student** tmp = new Student*();
				*tmp = EntryBlock->FindLastStudent();
				_block[i]->~Student();
				_block[i] = *tmp;
				EntryBlock->DeleteLastElement();
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
		EntryBlock->LoadInFile();
	}
}

void Block::DeleteLastElement()
{
	if (_block.size() == 5 && nextBlock != nullptr)
	{
		nextBlock->DeleteLastElement();
	}
	else if (_block.size() <= 5 && nextBlock == nullptr)
	{
		_block.erase(_block.begin() + _block.size() - 1);
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

void Block::ShowBlock(int shift)
{
	this->LoadFromFile(shift);
	if (_block.size() > 0)
	{
		for (size_t i = 0; i < _block.size(); i++)
		{
			_block[i]->GetInfo();
			if (i == 4 && nextBlock == nullptr)
			{
				nextBlock = new Block();
				nextBlock->ShowBlock(++shift);
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
			outf.write((char*)student, sizeof(Student));
		}
		if(nextBlock != nullptr) nextBlock->LoadInFile(outf);
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
			ofstream.write((char*)student, sizeof(Student));
		}
		if (nextBlock != nullptr)
			nextBlock->LoadInFile(ofstream);
	}
}

void Block::LoadFromFile(int shift)
{
	std::ifstream ifs("Block.bin");
	if (ifs)
	{
		Student tmp;
		ifs.seekg(sizeof(Student)*shift*5);
		ifs.read((char*)&tmp, sizeof(Student));
		while (!ifs.eof())
		{
			_block.push_back(new Student(tmp));
			if (ifs.eof() || _block.size() == 5)
			{
				break;
			}
			ifs.read((char*)&tmp, sizeof(Student));
		}
	}
	else std::cout << "Couldn't open file for writing!\n";
}

Student* Block::CheckIndex(int index)
{
	return EntryBlock->FindStudent(index);
}

Student* Block::FindStudent(int index, int shift)
{
	//Find the student by index in the vector 
	//Return pointer on the student
	this->LoadFromFile(shift);
	if (_block.size() > 0)
	{
		for (size_t i = 0; i < _block.size(); i++)
		{
			if (_block[i]->GetIndex() == index)
			{
				return _block[i];
			}
			if (i == 4)
			{
				nextBlock = new Block();
				return nextBlock->FindStudent(index, ++shift);
			}
		}
	}
	return nullptr;
}

Student* Block::FindLastStudent()
{
	std::ifstream ifs("Block.bin");
	if (ifs.is_open())
	{
		Student tmp;
		ifs.seekg(sizeof(Student), std::ios::end);
		ifs.read((char*)&tmp, sizeof(Student));
		return &tmp;
	}
	else return nullptr;
	/*if (_block.size() == 5 && nextBlock != nullptr)
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
	else return nullptr;*/

}
