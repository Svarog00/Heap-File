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
    Block block;
    char key;
    int tmpKey;
    while (true)
    {
        ShowMenu();
        std::cin >> key;
        switch (key)
        {
        case '1':
            block.AddStudent();
            break;
        case '2':
            std::cin >> tmpKey;
            block.ChangeStudent(tmpKey);
            break;
        case '3':
            std::cin >> tmpKey;
            block.DeleteStudent(tmpKey);
            break;
        case '4':
            std::cin >> tmpKey;
            block.FindStudent(tmpKey);
            break;

        }
    }
}

inline void ShowMenu()
{
    std::cout << "1 - Add new student" << std::endl
        << "2 - Edit student" << std::endl
        << "3 - Delete student" << std::endl
        << "4 - Find student" << std::endl;
}