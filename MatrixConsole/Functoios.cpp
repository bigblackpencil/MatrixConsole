#include <iostream>
#include <conio.h>
#include "Functions.h"
#include "Matrix.h"


void AboutProgram()
{
    using namespace std;

    for (int i = 0; i < 33; i++) {
        cout << "#";
    }
    cout << endl << "#\t\t\t\t#" << endl
        << "#\tОбратная матрица\t#" << endl
        << "#\tИ возможно что-то еще\t#" << endl
        << "#\t\t\t\t#" << endl
        << "#\t\t\t\t#" << endl
        << "# Автор: Unknown\t#" << endl;
    for (int i = 0; i < 33; i++) {
        cout << "#";
    }
    cout << endl << "#\t\t\t\t#" << endl << "#\t\t\t\t#" << endl;
}

int MenuSelect(int* count)
{
    int c = -1;
    std::cout << " \t   MENU \t\t \n\n"
        << "Enter matrix use keyboard           - 1\n\n"
        << "Enter matrix out a file             - 2\n\n"
        << "Enter 2 matrices for miltiplication - 3\n\n"
        << "Enter 2 matrices for add/sub        - 4\n\n"
        << "Clear console                       - 5\n\n"
        << "Exit                                - 6\n\n";
    while (true)
    {
        try
        {
            (*count)++;
            std::cout << "\nEnter point: ";
            if (*count > 1)
            {
                std::cin.clear(); // Сбросить флаги ошибки
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            std::cin >> c;
            if ((std::cin.fail() != 0) || c < 1 || c > 6)
            {
                std::cin.clear();
                throw MatrixException(7);
            }
            break;

        }
        catch (MatrixException Exc)
        {
            std::cout << Exc.Error() << std::endl;
        }
    }
    return c;
}


void ClearConsole()
{
    for (int i = 0; i < 25; i++)
        std::cout << std::endl;
}

double** AllocMemmorySqMatrix(int size)
{
    try
    {
        if (size <= 0)
        {
            throw MatrixException(8);
        }
        double** SqMatrix = new double* [size];

        for (int i = 0; i < size; i++)
            SqMatrix[i] = new double[size];

        return SqMatrix;
    }
    catch (std::bad_alloc)
    {
        throw MatrixException(6);
    }

}

double** AllocMemmoryMatrix(int rows, int cols)
{
    try
    {
        if (rows <= 0 || cols <= 0)
        {
            throw MatrixException(8);
        }
        double** Matrix = new double* [rows];

        for (int i = 0; i < rows; i++)
            Matrix[i] = new double[cols];

        return Matrix;
    }
    catch (std::bad_alloc)
    {
        throw MatrixException(6);
    }

}
//
void FreeMemmorySqMatrix(double** SqMatrix, int size)
{
    for (int i = 0; i < size; i++)
        delete[] SqMatrix[i];

    delete[] SqMatrix;
}
//
void PrintSqMatrix(double** Matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << Matrix[i][j] << "\t";
        }
        std::cout << "\n";
    }
    for (int i = 0; i < 5; i++)
    {
        std::cout << "\n";  //отступ после вывода матрицы
    }
}
//
double** MultipByNumber(double** Matrix, int size, double value)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            Matrix[i][j] *= value;
        }
    }

    return Matrix;
}

double** Transposition(double** Matrix, int rows, int cols)
{
    double** TrMatrix = new double* [cols];
    for (int i = 0; i < cols; i++)
    {
        TrMatrix[i] = new double[rows];
        for (int j = 0; j < rows; j++)
        {
            TrMatrix[i][j] = Matrix[j][i];
        }
    }

    return TrMatrix;
}
//
double Determinant(double** SqMatrix, int size)//Разложение по первой строчке   РАЗОБРАТЬ!!!
{
    if (size == 1)
        return SqMatrix[0][0];

    double det = 0;

    double** Minor = new double* [size - 1];
    for (int i = 0; i < size - 1; i++)
        Minor[i] = new double[size - 1];

    for (int col = 0; col < size; col++)
    {
        int minorRow = 0;
        for (int i = 1; i < size; i++)
        {
            int minorCol = 0;
            for (int j = 0; j < size; j++)
            {
                if (j == col)
                    continue;
                Minor[minorRow][minorCol] = SqMatrix[i][j];
                minorCol++;
            }
            minorRow++;
        }
        double minorDet = Determinant(Minor, size - 1);
        det += SqMatrix[0][col] * ((col % 2 == 0) ? 1 : -1) * minorDet;
    }

    FreeMemmorySqMatrix(Minor, size - 1);

    return det;
}
//
double** AlliedMatrix(double** SqMatrix, int size)//РАЗОБРАТЬ!!!
{
    if (size <= 1)
    {
        std::cout << "For allied matrix: \n";
        throw MatrixException(3);
    }

    double** Allied = new double* [size];
    for (int i = 0; i < size; ++i)
        Allied[i] = new double[size];

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            // Вычисляем минор
            double** minor = new double* [size - 1];
            for (int k = 0; k < size - 1; ++k) {
                minor[k] = new double[size - 1];
            }

            int minorRow = 0;
            for (int m = 0; m < size; ++m) {
                if (m == i) continue;
                int minorCol = 0;
                for (int n = 0; n < size; ++n) {
                    if (n == j) continue;
                    minor[minorRow][minorCol] = SqMatrix[m][n];
                    minorCol++;
                }
                minorRow++;
            }

            double minorDet = Determinant(minor, size - 1);

            Allied[i][j] = minorDet * ((i + j) % 2 == 0 ? 1 : -1);

            FreeMemmorySqMatrix(minor, size - 1);
        }
    }

    return Allied;
}
//
double** InverseMatrix(double** SqMatrix, int size)
{
    double** Allied = Transposition(AlliedMatrix(SqMatrix, size), size, size);
    double det = Determinant(SqMatrix, size);

    double** Inverse = new double* [size];
    for (int i = 0; i < size; i++)
    {
        Inverse[i] = new double[size];
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            Inverse[i][j] = Allied[i][j] / det;
        }
    }

    FreeMemmorySqMatrix(Allied, size);

    return Inverse;
}

void MenuTypeOutput()
{
    std::cout << "Чтобы вывести меню нажмите любую клавишу...\n";
    _getch();
    std::cout << std::endl;
}

double** MultipMatrrixes(double** Matrix1, double** Matrix2, int row1, int cols1, int cols2)
{
    double** ResultMatr = AllocMemmoryMatrix(row1, cols2); // for result Matrix

    for (int i = 0; i < row1; i++)
    {
        for (int j = 0; j < cols2; j++)
        {
            ResultMatr[i][j] = 0;
            for (int k = 0; k < cols1; k++)
            {
                ResultMatr[i][j] += Matrix1[i][k] * Matrix2[k][j];

            }
        }
    }


    return ResultMatr;
}

void EnterFromKeyboard()
{
    double value;
    int sizeSqMatrix;
    try
    {
        std::cout << "Enter size of square matrix: ";
        std::cin >> sizeSqMatrix;
        if (std::cin.fail())
        {
            std::cin.clear();
            throw MatrixException(5);
        }
        else if (sizeSqMatrix < 1)
        {
            std::cin.clear();
            throw MatrixException(8);
        }
        double** SqMatrix = AllocMemmorySqMatrix(sizeSqMatrix);

        std::cout << "Enter elements of square matrix: \n";
        double element;
        for (int i = 0; i < sizeSqMatrix; i++)
        {
            for (int j = 0; j < sizeSqMatrix; j++)
            {
                std::cout << "Enter a element (" << i + 1 << "," << j + 1 << ") : ";
                std::cin >> element;
                if (std::cin.fail())
                {
                    std::cin.clear();
                    throw MatrixException(9);
                }
                SqMatrix[i][j] = element;
            }
        }
        std::cout << "\nYour square matrix: \n";
        PrintSqMatrix(SqMatrix, sizeSqMatrix, sizeSqMatrix);

        /*
        * Транспонирование матрицы
        */
        double** TranspositionMatrix = Transposition(SqMatrix, sizeSqMatrix, sizeSqMatrix);
        std::cout << "Транспонированная введенная матрица: \n";
        PrintSqMatrix(TranspositionMatrix, sizeSqMatrix, sizeSqMatrix);
        FreeMemmorySqMatrix(TranspositionMatrix, sizeSqMatrix);

        /*
        * Определитель матрицы
        */
        std::cout << "Определитель матрицы: ";
        std::cout << Determinant(SqMatrix, sizeSqMatrix) << "\n\n";
        if (Determinant(SqMatrix, sizeSqMatrix) == 0)
        {
            throw MatrixException(2);
        }
        /*
        *Союзная матрица
        */
        double** AlliedMart = AlliedMatrix(SqMatrix, sizeSqMatrix);
        std::cout << "Сщюзная матрица: \n\n\n";
        PrintSqMatrix(AlliedMart, sizeSqMatrix, sizeSqMatrix);
        FreeMemmorySqMatrix(AlliedMart, sizeSqMatrix);

        /*
        * Обратная матрица
        */
        double** Inverse = InverseMatrix(SqMatrix, sizeSqMatrix);
        std::cout << "Invert матрица: \n\n\n";
        PrintSqMatrix(Inverse, sizeSqMatrix, sizeSqMatrix);
        FreeMemmorySqMatrix(Inverse, sizeSqMatrix);


        std::cout << "Enter a number by which you want to multiply the matrix: ";
        std::cin >> value;
        if (std::cin.fail())
        {
            std::cin.clear();

            throw MatrixException(9);
        }
        MultipByNumber(SqMatrix, sizeSqMatrix, value);

        std::cout << "\nYour square matrix multiplated by a number: \n";
        PrintSqMatrix(SqMatrix, sizeSqMatrix, sizeSqMatrix);

        FreeMemmorySqMatrix(SqMatrix, sizeSqMatrix);
    }
    catch (MatrixException Exc)
    {
        std::cout << Exc.Error() << "\n\n";
    }
}

void EnterFromKeyboardForMul()
{
    int rows1{}, cols1{}, rows2{}, cols2{};
    try
    {
        std::cout << "Enter size of the first matix:\n";
        std::cout << "Enter number of rows: ";
        std::cin >> rows1;
        if (std::cin.fail() != 0 || rows1 <= 0)
        {
            std::cin.clear();
            throw MatrixException(8);
        }
        std::cout << "Enter number of columns: ";
        std::cin >> cols1;
        if (std::cin.fail() != 0 || cols1 <= 0)
        {
            std::cin.clear();
            throw MatrixException(8);
        }

        std::cout << "\n\nEnter size of the second matix:\n";
        std::cout << "Enter number of rows: ";
        std::cin >> rows2;
        if (std::cin.fail() != 0 || rows2 <= 0)
        {
            std::cin.clear();
            throw MatrixException(8);
        }
        else if (cols1 != rows2)
        {
            std::cin.clear();
            throw MatrixException(15);
        }
        std::cout << "Enter number of coloumns: ";
        std::cin >> cols2;
        if (std::cin.fail() != 0 || cols2 <= 0)
        {
            std::cin.clear();
            throw MatrixException(8);
        }



        double** Matrix1 = AllocMemmoryMatrix(rows1, cols1);

        std::cout << "Enter elements of the second matrix: \n";
        double elementFirstMatr{};
        for (int i = 0; i < rows1; i++)
        {
            for (int j = 0; j < cols1; j++)
            {
                std::cout << "Enter a element (" << i + 1 << "," << j + 1 << ") : ";
                std::cin >> elementFirstMatr;
                if (std::cin.fail())
                {
                    std::cin.clear();
                    throw MatrixException(9);
                }
                Matrix1[i][j] = elementFirstMatr;
            }
        }
        std::cout << "\nYour the first matrix: \n";
        PrintSqMatrix(Matrix1, rows1, cols1);

        double** Matrix2 = AllocMemmoryMatrix(rows2, cols2);

        std::cout << "Enter elements of the second matrix: \n";
        double elementSecondMatr{};
        for (int i = 0; i < rows2; i++)
        {
            for (int j = 0; j < cols2; j++)
            {
                std::cout << "Enter a element (" << i + 1 << "," << j + 1 << ") : ";
                std::cin >> elementSecondMatr;
                if (std::cin.fail())
                {
                    std::cin.clear();
                    throw MatrixException(9);
                }
                Matrix2[i][j] = elementSecondMatr;
            }
        }
        std::cout << "\nYour the second matrix: \n";
        PrintSqMatrix(Matrix2, rows2, cols2);

        double** ResultMatrix = MultipMatrrixes(Matrix1, Matrix2, rows1, cols1, cols2);
        std::cout << "Result:\n\n";
        PrintSqMatrix(ResultMatrix, rows1, cols2);

        FreeMemmorySqMatrix(Matrix1, rows1);
        FreeMemmorySqMatrix(Matrix2, rows2);
        FreeMemmorySqMatrix(ResultMatrix, rows2);
    }
    catch (MatrixException Exc)
    {
        std::cout << Exc.Error() << '\n';
    }

}

double** AddSubMatrices(double** Matrix1, double** Matrix2, int rows, int cols, int addsub)
{
    if (addsub == 1)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                Matrix1[i][j] += Matrix2[i][j];
            }
        }
    }
    else if (addsub == 2)
    {

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                Matrix1[i][j] -= Matrix2[i][j];
            }
        }
    }

    return Matrix1;
}

void EnterFromKeyboardForAddorSub(short addsub)
{
    int rows{}, cols{};
    try
    {
        std::cout << "Enter size of the matices:\n";
        std::cout << "Enter number of rows: ";
        std::cin >> rows;
        if (std::cin.fail() != 0 || rows <= 0)
        {
            std::cin.clear();
            throw MatrixException(8);
        }
        std::cout << "Enter number of columns: ";
        std::cin >> cols;
        if (std::cin.fail() != 0 || cols <= 0)
        {
            std::cin.clear();
            throw MatrixException(8);
        }

        double** Matrix1 = AllocMemmoryMatrix(rows, cols);

        std::cout << "Enter elements of the second matrix: \n";
        double elementFirstMatr{};
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                std::cout << "Enter a element (" << i + 1 << "," << j + 1 << ") : ";
                std::cin >> elementFirstMatr;
                if (std::cin.fail())
                {
                    std::cin.clear();
                    throw MatrixException(9);
                }
                Matrix1[i][j] = elementFirstMatr;
            }
        }
        std::cout << "\nYour the first matrix: \n";
        PrintSqMatrix(Matrix1, rows, cols);

        double** Matrix2 = AllocMemmoryMatrix(rows, cols);

        std::cout << "Enter elements of the second matrix: \n";
        double elementSecondMatr{};
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                std::cout << "Enter a element (" << i + 1 << "," << j + 1 << ") : ";
                std::cin >> elementSecondMatr;
                if (std::cin.fail())
                {
                    std::cin.clear();
                    throw MatrixException(9);
                }
                Matrix2[i][j] = elementSecondMatr;
            }
        }
        std::cout << "\nYour the first matrix: \n";
        PrintSqMatrix(Matrix2, rows, cols);

        double** ResultMatrix = AddSubMatrices(Matrix1, Matrix2, rows, cols, addsub);
        std::cout << "Result:\n\n";
        PrintSqMatrix(ResultMatrix, rows, cols);

        FreeMemmorySqMatrix(Matrix1, rows);
        FreeMemmorySqMatrix(Matrix2, rows);
    }
    catch (MatrixException Exc)
    {
        std::cout << Exc.Error() << '\n';
    }
}

void FromBinaryFile()
{

}
