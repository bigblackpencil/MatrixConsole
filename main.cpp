#include <iostream>
#include <conio.h>
#include "Matrix.h"
#include "Functions.h"


//int CorrectionInput(double** Matrix)
//{
//    int element = 0;
//    int row = -1, col = -1;
//
//    std::cout << L"Корректировать введенные данные?\n"
//              << "[1] - для исправления введенных данных\n"
//              << "[Любая другая клавиша] - для продолжения вычислений\n"
//              << "Выбор: ";
//
//    std::cin >> element;
//    std::cout << "\n\n";
//    if (std::cin.fail() != 0) {
//        std::cin.clear();
//    }
//    if (element == 1) {
//        try {
//            std::cout << L"Введите номер СТРОКИ исправляемого элемента: ";
//            std::cin >> row;
//            if ((std::cin.fail() != 0) || (row < 1 || row > Matrix_size())) {
//                std::cin.clear();
//                throw MatrixException(13);
//            }
//            std::cout << L"Введите номер СТОЛБЦА исправляемого элемента: ";
//            std::cin >> col;
//            if ((std::cin.fail() != 0) || (col < 1 || col > Matrix->size)) {
//                std::cin.clear();
//                throw MatrixException(14);
//            }
//            std::cout << L"[" << row << "," << col << "] " << Matrix[row - 1][col - 1] << " --> ";
//            std::cin >> element;
//            std::cout << std::endl;
//            if (std::cin.fail() != 0) {
//                std::cin.clear();
//                throw MatrixException(9);
//            }
//            Matrix[row - 1][col - 1] = element;
//        }
//        catch (MatrixException Exc) {
//            std::cout << Exc.Error() << "\n\n";
//        }
//    }
//    else {
//        return -1;
//    }
//    return 0;
//}

int main()
{
   
    setlocale(LC_ALL, "Russian");
    AboutProgram();

    short addsub{};
    char choice{};
    while (true)
    {
        int count = 0;
        int* ptr = &count;//непонятно для чего
        choice = MenuSelect(ptr);
        switch (choice)
        {
        case 1:
            EnterFromKeyboard();
            MenuTypeOutput();
            break;
        case 2:
            FromBinaryFile();
            MenuTypeOutput();
            break;
        case 3:
            EnterFromKeyboardForMul();
            MenuTypeOutput();
            break;
        case 4:
            std::cout << "You chose point addition or subtraction Matrices.\n"
                      << "If you want to fold matrices then press 1 else for matices subtraction press 2: ";
            try
            {
                std::cin >> addsub;
                if ((std::cin.fail() != 0) || addsub < 1 || addsub > 2)
                {
                    std::cin.clear();
                    throw MatrixException(7);
                }
            }
            catch (MatrixException Exc)
            {
                std::cout << Exc.Error() << '\n';
            }

            EnterFromKeyboardForAddorSub(addsub);
            MenuTypeOutput();
            break;
        case 5:
            ClearConsole();
            break;
        case 6:
            exit(0);
        }
    }
    getchar();
    
    return 0;
}
