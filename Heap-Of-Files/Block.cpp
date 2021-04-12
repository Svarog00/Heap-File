#include <fstream>
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include "Block.h"

Block* Block::EntryBlock = nullptr;
int Block::num = 0;

Block::Block(bool init)
{
	nextBlock = nullptr;
	if (init)
	{
		//LoadFromFile();
		EntryBlock = this;
	}
}

void Block::AddStudent()
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
	EntryBlock->Clear();
	delete tmp;
	std::cout << "\nSecond name: ";
	std::cin >> secondName;
	std::cout << "\nName: ";
	std::cin >> name;
	std::cout << "\nThird name: ";
	std::cin >> thirdName;
	std::cout << "\nGroup index: ";
	std::cin >> groupIndex;
	
	std::ofstream outf("Block.bin", std::ios::binary | std::ios::app);
	/*if (num % 5 == 0)
	{
		outf.seekp(sizeof(Student) * num);
		outf.write("", sizeof(Student)*5);
	}*/
	outf.seekp(sizeof(Student)*num);
	outf.write((char*)new Student(index, name, secondName, thirdName, groupIndex), sizeof(Student));
	num++;
}

void Block::ChangeStudent(int index, int shift)
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
	delete student;
	EntryBlock->Clear();
}

void Block::DeleteStudent(int index, int shift)
{
	//Find the index of the student in the vector
	//erase it from vector
	LoadFromFile(shift);
	if (_block.size() > 0)
	{
		for (size_t i = 0; i < _block.size(); i++)
		{
			if (_block[i]->GetIndex() == index)
			{
				Student* tmp;
				tmp = new Student(*(EntryBlock->FindLastStudent()));
				delete _block[i];
				_block[i] = new Student(*tmp);
				delete tmp;
				EntryBlock->LoadInFile();
				EntryBlock->DeleteLastElement();
				break;
			}
			else if (i == 4 && nextBlock != nullptr)
			{
				nextBlock->DeleteStudent(index, ++shift);
			}
			else if(i == 4 && nextBlock == nullptr)
			{
				std::cout << "There is no such student\n";
			}
		}
	}
	EntryBlock->Clear();
}

void Block::DeleteLastElement()
{
	int file;
	_sopen_s(&file, "Block.bin", _O_RDWR, _SH_DENYNO, _S_IREAD | _S_IWRITE);
	_chsize_s(file, _filelength(file)-sizeof(Student));
}

void Block::ShowStudent(int index)
{
	//Find student by index and show info
	Student* student = FindStudent(index);
	if (student == nullptr)
		std::cout << "There is no such student\n";
	else 
		student->GetInfo();

	EntryBlock->Clear();
}

void Block::ShowBlock(int shift)
{
	this->LoadFromFile(shift);
	if (_block.size() > 0)
	{
		for (size_t i = 0; i < _block.size(); i++)
		{
			_block[i]->GetInfo();
			if (i == 4)
			{
				if(nextBlock == nullptr)
					nextBlock = new Block(false);
				nextBlock->ShowBlock(++shift);
			}
		}
	}
	EntryBlock->Clear();
}

void Block::LoadInFile()
{
	std::ofstream outf("Block.bin", std::ios::binary | std::ios::ate);
	outf.seekp(0);
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
			if (ifs.eof() || _block.size() == 5 || _block.size() == num - shift * 5)
			{
				break;
			}
			ifs.read((char*)&tmp, sizeof(Student));
		}
	}
	else std::cout << "Couldn't open file for writing!\n";
}

void Block::Clear()
{
	Block* ptr = EntryBlock;
	while(ptr != nullptr)
	{
		ptr->_block.clear();
		ptr = ptr->nextBlock;

	}
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
				nextBlock = new Block(false);
				return nextBlock->FindStudent(index, ++shift);
			}
		}
	}
	return nullptr;
}

Student* Block::FindLastStudent()
{
	std::ifstream ifs("Block.bin", std::ios::binary);
	if (ifs.is_open())
	{
		Student tmp;
		ifs.seekg(-200, std::ios::end);
		ifs.read((char*)&tmp, sizeof(Student));
		return &tmp;
	}
	else return nullptr;
}
