#include <fstream>
#include <iostream>
#include <io.h>
#include <fcntl.h>
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
}

void Block::DeleteStudent(int index)
{
	//Find the index of the student in the vector
	//erase it from vector
	fileManager.Reopen();
	Student* tmp = FindStudent(index);
	if (tmp != nullptr)
	{
		//Erase student 
		fileManager.Reopen();
		Container tmpBlock = Container();
		fileManager.LoadLastBlock(&tmpBlock, sizeof(Container));
		for (int i = 0; i < 5; i++)
		{
			if (tmpBlock.block[i].GetIndex() == -1)
			{
				*tmp = Student(tmpBlock.block[i - 1]);
				tmpBlock.block[i - 1] = Student();
				break;
			}
		}
		fileManager.LoadInFile(&_block, shift*sizeof(Container), sizeof(Container));
		fileManager.LoadInFile(&tmpBlock, num*sizeof(Container), sizeof(Container));
	}
	else std::cout << "There is no such student" << std::endl;
	//Ќаходим блок с нужным студентом, подгружаем последний блок. ќбмениваем значени€ между нужным слотом в блоке и последним студентом. ќбнул€ем последнего студента
	
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
}

//void Block::ShowBlock(int shift)
//{
//	this->LoadFromFile(shift);
//	if (_block.size() > 0)
//	{
//		for (size_t i = 0; i < _block.size(); i++)
//		{
//			_block[i]->GetInfo();
//			if (i == 4)
//			{
//				if(nextBlock == nullptr)
//					nextBlock = new Block(false);
//				nextBlock->ShowBlock(++shift);
//			}
//		}
//	}
//}
//
//void Block::LoadInFile()
//{
//	std::ofstream outf("Block.bin", std::ios::binary | std::ios::ate);
//	outf.seekp(0);
//	if (outf)
//	{
//		for (auto student : _block)
//		{
//			outf.write((char*)student, sizeof(Student));
//		}
//		if(nextBlock != nullptr) nextBlock->LoadInFile(outf);
//		std::cout << "Block has been loaded in file!\n";
//	}
//	else std::cout << "Couldn't open file for writing!\n";
//	outf.close();
//}

//void Block::LoadInFile(std::ofstream& ofstream)
//{
//	if (ofstream)
//	{
//		for (auto student : _block)
//		{
//			ofstream.write((char*)student, sizeof(Student));
//		}
//		if (nextBlock != nullptr)
//			nextBlock->LoadInFile(ofstream);
//	}
//}
//
//void Block::LoadFromFile(int shift)
//{
//	std::ifstream ifs("Block.bin");
//	if (ifs)
//	{
//		Student tmp;
//		ifs.seekg(sizeof(Student)*shift*5);
//		ifs.read((char*)&tmp, sizeof(Student));
//		while (!ifs.eof())
//		{
//			_block.push_back(new Student(tmp));
//			if (ifs.eof() || _block.size() == 5) //|| _block.size() == num - shift * 5
//			{
//				break;
//			}
//			ifs.read((char*)&tmp, sizeof(Student));
//		}
//	}
//	else std::cout << "Couldn't open file for writing!\n";
//}

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
	while (shift * sizeof(Container) < fileManager.GetEndOfFile())
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
