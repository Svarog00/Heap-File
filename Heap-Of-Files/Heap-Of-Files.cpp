#include <iostream>
#include <vector>
#include <conio.h>
#include "StudentClass.h"
#include "Block.h"
 

/*
В программе должны быть реализованы следующие функции:
· добавление информации о студент;
· изменение информации о студенте;
· удаление информации о студенте;
· осуществление поиска информации о студенте.
*/

inline void ShowMenu();

int main()
{
    Block* blockEntry = new Block();
    char key;
    int tmpKey;
    while (true)
    {
        ShowMenu();
        std::cin >> key;
        switch (key)
        {
        case '1':
            blockEntry->AddStudent();
            break;
        case '2':
            std::cout << "What index?\n";
            std::cin >> tmpKey;
            blockEntry->ChangeStudent(tmpKey);
            break;
        case '3':
            std::cout << "What index?\n";
            std::cin >> tmpKey;
            blockEntry->DeleteStudent(tmpKey);
            break;
        case '4':
            std::cout << "What index?\n";
            std::cin >> tmpKey;
            blockEntry->ShowStudent(tmpKey);
            break;
        case '5':
            blockEntry->ShowBlock();
            break;
        case '6':
            blockEntry->LoadInFile();
            break;
        case '7':
            blockEntry->LoadFromFile();
            break;
        default:
            std::cout << "Wrong command!" << std::endl;
            system("cls");
            break;
        }
    }
}

inline void ShowMenu()
{
    std::cout << "\n1 - Add new student" << std::endl
        << "2 - Edit student" << std::endl
        << "3 - Delete student" << std::endl
        << "4 - Find student" << std::endl
        << "5 - Show all of the students" << std::endl
        << "6 - Load block in file" << std::endl
        << "7 - Load block from file" << std::endl;
}