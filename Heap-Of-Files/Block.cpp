#include <fstream>
#include <iostream>
#include "Block.h"
#include "FileManager.h"

Block* Block::EntryBlock = nullptr;
int Block::num = 0;

Container::Container()
{
	for (int i = 0; i < 5; i++)
		block[i] = Student();
}

Block::Block(bool init)
{
	shift = 0;
	std::string tmp = "Block.bin";
	fileManager = FileManager(tmp);
	if (!fileManager.CheckBlock())
	{
		_block = Container();
	}
	else
	{
		num = fileManager.LoadLastFromFile(&_block, sizeof(Container)); //ѕолучаем кол-во блоков и загружаем последний.
	}
	EntryBlock = this;
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
	delete tmp;
	std::cout << "\nSecond name: ";
	std::cin >> secondName;
	std::cout << "\nName: ";
	std::cin >> name;
	std::cout << "\nThird name: ";
	std::cin >> thirdName;
	std::cout << "\nGroup index: ";
	std::cin >> groupIndex;

	if (_block.block[4].GetIndex() != -1) //≈сли блок уже заполнен, то создаем новый и запихиваем в начало новую запись
	{
		_block = Container();
		_block.block[0] = Student(index, name, secondName, thirdName, groupIndex);
		num++;	
	}
	else //¬о всех остальных случа€ запихиваем на пустое место
	{
		for (int i = 0; i < 5; i++)
		{
			if (_block.block[i].GetIndex() == -1)
			{
				_block.block[i] = Student(index, name, secondName, thirdName, groupIndex);
				break;
			}
		}
	}
	fileManager.Reopen();
	fileManager.LoadInFile(&_block, num*sizeof(Container), sizeof(Container)); //√рузим блок в файл
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
		fileManager.Reopen();
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
			fileManager.LoadInFile(&_block, shift * sizeof(Container), sizeof(Container));
			break;
		}
		case 2:
		{
			std::string newName;
			std::cout << "New second name: \n";
			std::cin >> newName;
			student->SetSecondName(newName);
			fileManager.LoadInFile(&_block, shift * sizeof(Container), sizeof(Container));
			break;
		}
		case 3:
		{
			std::string newName;
			std::cout << "New third name: \n";
			std::cin >> newName;
			student->SetThirdName(newName);
			fileManager.LoadInFile(&_block, shift * sizeof(Container), sizeof(Container));
			break;
		}
		case 4:
		{
			int newGroupIndex;
			std::cout << "New group index: \n";
			std::cin >> newGroupIndex;
			student->SetGroupIndex(newGroupIndex);
			fileManager.LoadInFile(&_block, shift * sizeof(Container), sizeof(Container));
			break;
		}
		default:
			std::cout << "Wrong command\n";
			break;
		}
	}
	student = nullptr;
	delete student;
}

void Block::DeleteStudent(int index)
{
	bool sameBlock = false;
	//Find the index of the student in the vector
	//erase it from vector
	fileManager.Reopen();
	Student* tmp = FindStudent(index);
	if (tmp != nullptr)
	{
		fileManager.Reopen();
		Container* tmpBlock = new Container();
		fileManager.LoadLastBlock(tmpBlock, sizeof(Container));
		if (_block.block[0].GetIndex() == tmpBlock->block[0].GetIndex())
		{
			sameBlock = true;
			tmpBlock = &_block;
		}
		for (int i = 0; i < 5; i++)
		{
			if (tmpBlock->block[i].GetIndex() == -1)
			{
				*tmp = Student(tmpBlock->block[i-1]);
				tmpBlock->block[i-1] = Student();
				break;
			}
			else if (i == 4)
			{
				*tmp = Student(tmpBlock->block[i]);
				tmpBlock->block[i] = Student();
				break;
			}
		}
		fileManager.LoadInFile(&_block, shift*sizeof(Container), sizeof(Container));
		if (!sameBlock)
		{
			fileManager.LoadInFile(tmpBlock, num * sizeof(Container), sizeof(Container));
		}
		else if(tmpBlock->block[0].GetIndex() == -1)
		{
			num--;
			fileManager.DeleteLastBlock(sizeof(Container));
		}
	}
	else std::cout << "There is no such student" << std::endl;
	tmp = nullptr;
	delete tmp;
	//Ќаходим блок с нужным студентом, подгружаем последний блок. ќбмениваем значени€ между нужным слотом в блоке и последним студентом. ќбнул€ем последнего студента
	
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
	shift = 0;
	fileManager.Reopen();
	fileManager.LoadFromFile(&_block, shift * sizeof(Container), sizeof(Container));
	bool canWork = true;
	while (shift <= num && canWork)
	{
		if (_block.block[0].GetIndex() != -1)
		{
			for (size_t i = 0; i < 5; i++)
			{
				if (_block.block[i].GetIndex() != -1)
				{
					_block.block[i].GetInfo();
				}
				else
				{
					canWork = false;
					break;
				}
				if (i == 4)
				{
					shift++;
				}
			}
			if (shift <= num) fileManager.LoadFromFile(&_block, shift * sizeof(Container), sizeof(Container));
			else break;
		}
		else break;
	}
}

void Block::Exit()
{
	fileManager.Close();
}

Student* Block::CheckIndex(int index)
{
	return EntryBlock->FindStudent(index);
}

Student* Block::FindStudent(int index)
{
	//Find the student by index in the vector 
	//Return pointer on the student
	shift = 0;
	fileManager.Reopen();
	fileManager.LoadFromFile(&_block, shift * sizeof(Container), sizeof(Container));
	//ѕока не достигнут конец файла, загружаем блок, провер€ем есть ли в блоке что-то, если в полученном блоке нет нужного студента - увеличиваем смещение и грузим следующий.
	//shift * sizeof(Container) < fileManager.GetEndOfFile()
	while (shift <= num)
	{
		if (_block.block[0].GetIndex() != -1)
		{
			for (size_t i = 0; i < 5; i++)
			{
				if (_block.block[i].GetIndex() == index)
				{
					return &_block.block[i];
				}
				if (i == 4)
				{
					++shift;
				}
			}
			if (shift * sizeof(Container) >= fileManager.GetEndOfFile())
				break;
			else fileManager.LoadFromFile(&_block, shift * sizeof(Container), sizeof(Container));
		}
		else break;
	}
	return nullptr;
}
