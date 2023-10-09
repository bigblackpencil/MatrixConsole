#include <iostream>
#include <conio.h>
#include "Matrix.h"
#include "Functions.h"


int main()
{
   
    setlocale(LC_ALL, "Russian");
    AboutProgram();

    short addsub{};
    char choice{};
    while (true)
    {
        int count = 0;
        int* ptr = &count;
        choice = MenuSelect(ptr);
        switch (choice)
        {
        case 1:
            EnterFromKeyboard();
            MenuTypeOutput();
            break;
        case 2:
            SqMatrixFromBinaryFile();
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
