#pragma once
#include <fstream>

class FileManager
{
private:
	std::fstream fs;
	std::string path;
public:
	FileManager();
	FileManager(std::string path);

	void LoadInFile(void* block, int shift, int size);
	void LoadFromFile(void* block, int shift, int size);
	int LoadLastFromFile(void* block, int size);
	void LoadLastBlock(void* block, int size);
	void Close();
	void Reopen();
	void DeleteLastBlock(int size);

	int GetEndOfFile();
	bool CheckBlock();
};