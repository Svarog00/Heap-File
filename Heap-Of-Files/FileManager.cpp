#include "FileManager.h"
#include "Block.h"

FileManager::FileManager() {}

FileManager::FileManager(std::string path)
{
	this->path = path;
	fs.open(path, std::ios::binary);
	fs.close();
	fs.open(this->path, std::ios::in | std::ios::out | std::ios::ate | std::ios::binary);
}

void FileManager::LoadInFile(void* block, int shift, int size)
{
	fs.seekp(shift, std::ios::beg);
	fs.write((char*)block, size);
}

void FileManager::LoadFromFile(void* block, int shift, int size)
{
	fs.seekg(shift, std::ios::beg);
	fs.read((char*)block, size);
}

int FileManager::LoadLastFromFile(void* block, int size)
{
	int num = 0;
	if (fs.is_open())
	{
		fs.close();
		fs.open(path, std::ios::in | std::ios::out | std::ios::ate | std::ios::binary);
		fs.seekg(0, std::ios::end);
		num = fs.tellg() / size - 1; //Возвращаем количество блоков -1, так как счет блоков идет с 0
		fs.seekg(size, std::ios::end);
		fs.read((char*)block, size);
	}
	return num;
}

void FileManager::LoadLastBlock(void* block, int size)
{
	fs.seekg(-size, std::ios::end);
	fs.read((char*)block, size);
}

void FileManager::Close()
{
	if (fs.is_open())
	{
		fs.close();
	}
}

void FileManager::Reopen()
{
	if (fs.is_open())
		fs.close();
	fs.open(path, std::ios::in | std::ios::out | std::ios::ate | std::ios::binary);
}

int FileManager::GetEndOfFile()
{
	fs.seekg(0, std::ios::end);
	int outp = 0;
	outp = fs.tellg();
	return outp;
}

bool FileManager::CheckBlock()
{
	if (fs.is_open())
	{
		fs.seekg(0, std::ios::end);
		if (fs.tellg() == 0)
			return false;
		else if (fs.tellg() % sizeof(Container) == 0)
		{
			return true;
		}
		else return false;
	}
	else return false;
}
