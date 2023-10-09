#include <iostream>
#include <conio.h>
#include "Functions.h"
#include "Matrix.h"
#include <fstream>


void AboutProgram()
{
    using namespace std;

    for (int i = 0; i < 65; i++) {
        cout << "#";
    }
    cout << endl << "#\t\t\t\t\t\t\t\t#" << endl
        << "#\tВычисление:\t\t\t\t\t\t#" << endl
        << "#\tОбратной матрицы\t\t\t\t\t#" << endl
        << "#\tПеремножение двух матриц\t\t\t\t#" << endl
        << "#\tСложение либо вычитание двух матриц\t\t\t#" << endl
        << "#\tМатрицы можно вводить с консоли, либо читать из файла\t#" << endl
        << "#\tРезультаты вычислений будут записаны в файлы\t\t#" << endl
        << "#\t\t\t\t\t\t\t\t#" << endl
        << "#\t\t\t\t\t\t\t\t#" << endl
        << "# Автор: BigBlackPencil\t\t\t\t\t\t#" << endl;
    for (int i = 0; i < 65; i++) {
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

void FreeMemmorySqMatrix(double** SqMatrix, int size)
{
    for (int i = 0; i < size; i++)
        delete[] SqMatrix[i];

    delete[] SqMatrix;
}

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
    double determinant = 0;

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
        * Корректирование введеных пользователем данных
        */
        while (CorrectionInput(SqMatrix, sizeSqMatrix, sizeSqMatrix) != -1) {
            std::cout << std::endl << "Главная матрица" << '\n';
            PrintSqMatrix(SqMatrix, sizeSqMatrix, sizeSqMatrix);
            std::cout << '\n';
        };

        /*
        * Транспонирование матрицы
        */
        double** TranspositionMatrix = Transposition(SqMatrix, sizeSqMatrix, sizeSqMatrix);
        std::cout << "Транспонированная введенная матрица: \n";
        PrintSqMatrix(TranspositionMatrix, sizeSqMatrix, sizeSqMatrix);

        /*
        * Определитель матрицы
        */
        determinant = Determinant(SqMatrix, sizeSqMatrix);
        std::cout << "Определитель матрицы: ";
        std::cout << determinant << "\n\n";
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

        /*
        * Обратная матрица
        */
        double** Inverse = InverseMatrix(SqMatrix, sizeSqMatrix);
        std::cout << "Invert матрица: \n\n\n";
        PrintSqMatrix(Inverse, sizeSqMatrix, sizeSqMatrix);

        SaveToFileSqMatrix(determinant, SqMatrix, TranspositionMatrix, AlliedMart, Inverse, sizeSqMatrix);

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

        FreeMemmorySqMatrix(TranspositionMatrix, sizeSqMatrix);
        FreeMemmorySqMatrix(AlliedMart, sizeSqMatrix);
        FreeMemmorySqMatrix(Inverse, sizeSqMatrix);
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

        /*
        * Корректирование введеных пользователем данных
        */
        while (CorrectionInput(Matrix1, rows1, cols1) != -1) {
            std::cout << std::endl << "Главная матрица" << '\n';
            PrintSqMatrix(Matrix1, rows1, cols1);
            std::cout << '\n';
        };

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

        /*
        * Корректирование введеных пользователем данных
        */
        while (CorrectionInput(Matrix2, rows2, cols2) != -1) {
            std::cout << std::endl << "Главная матрица" << '\n';
            PrintSqMatrix(Matrix2, rows2, cols2);
            std::cout << '\n';
        };

        double** ResultMatrix = MultipMatrrixes(Matrix1, Matrix2, rows1, cols1, cols2);
        SaveToFileMatrixMul(Matrix1, Matrix2, ResultMatrix, rows1, cols1, rows2, cols2);
        std::cout << "Result:\n\n";
        PrintSqMatrix(ResultMatrix, rows1, cols2);


        FreeMemmorySqMatrix(Matrix1, rows1);
        FreeMemmorySqMatrix(Matrix2, rows2);
        FreeMemmorySqMatrix(ResultMatrix, rows1);
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

        /*
        * Корректирование введеных пользователем данных
        */
        while (CorrectionInput(Matrix1, rows, cols) != -1) {
            std::cout << std::endl << "Главная матрица" << '\n';
            PrintSqMatrix(Matrix1, rows, cols);
            std::cout << '\n';
        };

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

        /*
        * Корректирование введеных пользователем данных
        */
        while (CorrectionInput(Matrix2, rows, cols) != -1) {
            std::cout << std::endl << "Главная матрица" << '\n';
            PrintSqMatrix(Matrix2, rows, cols);
            std::cout << '\n';
        };

        double** ResultMatrix = AddSubMatrices(Matrix1, Matrix2, rows, cols, addsub);
        std::cout << "Result:\n\n";
        PrintSqMatrix(ResultMatrix, rows, cols);

        SaveToFileMatrixAddSub(Matrix1, Matrix2, ResultMatrix, rows, cols);

        FreeMemmorySqMatrix(Matrix1, rows);
        FreeMemmorySqMatrix(Matrix2, rows);
    }
    catch (MatrixException Exc)
    {
        std::cout << Exc.Error() << '\n';
    }
}

void SqMatrixFromBinaryFile()
{
    using namespace std;

    int size;

    double** Matrix{};
    double determinant{};
    double** TransponMatr{};
    double** AlliedMatr{};
    double** InverseMatr{};


    cout << "\tВнимание!\t\n"
        << "\tДля корректной работы этого модуля программы\t\n"
        << "\tнеобходимо создать файл matrix.txt в следующем формате:\t\n"
        << "\tв первой сторке указывается размер матрицы (количесво сторок или столбцов)\t\n"
        << "\tматрица должна быть квадратная\t\n"
        << "\tбудет подсчитаны:\t\n"
        << "\tдетерминант:\t\n"
        << "\tтранспонированная матрица:\t\n"
        << "\tсоюзная матрица:\t\n"
        << "\tобратная матрица исходной:\t\n\n\n\n";

    try
    {
        ifstream fin("matrix.txt"); 

        if (!fin.is_open())
        {
            throw MatrixException(11);
        }

        fin >> size; // Первая строка файла должна содержать количество строк и столбцов матрицы

        if (1 == size)
        {
            throw MatrixException(3);
        }

        Matrix = AllocMemmorySqMatrix(size);

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                fin >> Matrix[i][j];
            }
        }

        fin.close();

        // Вывод матрицы для проверки
        PrintSqMatrix(Matrix, size, size);

        cout << "\n\n\n";

        determinant = Determinant(Matrix, size);
        if (0 == determinant)
        {
            throw MatrixException(2);
        }
        TransponMatr = Transposition(Matrix, size, size);
        AlliedMatr = AlliedMatrix(Matrix, size);
        InverseMatr = InverseMatrix(Matrix, size);

        cout << "детерминант: " << determinant << "\n\n";
        cout << "Траспонированная матрица: \n";
        PrintSqMatrix(TransponMatr, size, size);
        cout << "Союзная матрица: \n";
        PrintSqMatrix(AlliedMatr, size, size);
        cout << "Обратная матрица: \n";
        PrintSqMatrix(InverseMatr, size, size);

        FreeMemmorySqMatrix(Matrix, size);
        FreeMemmorySqMatrix(Matrix, size);
        FreeMemmorySqMatrix(Matrix, size);
        FreeMemmorySqMatrix(Matrix, size);
    }
    catch (MatrixException Exc)
    {
        cout << Exc.Error() << "\n\n";
    }

    SaveToFileSqMatrix(determinant, Matrix, TransponMatr, AlliedMatr, InverseMatr, size);
}

int SaveToFileSqMatrix(double determinant, double** SqMatr, double** TransponMatr, double** AlliedMatr, double** InverseMatr, int size)
{
    std::ofstream fout("results.txt", std::ios::app);
    try
    {
        if (!fout.is_open())
            throw MatrixException(10);

        fout << "Результаты:\n\n"
             << "Детерминант: " << determinant << "\n\n"
             << "Введенная матрица:\n\n";
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                fout << SqMatr[i][j] << "  ";
            }
            fout << '\n';
        }

        fout << "Транспонированная матрица:\n\n";
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                fout << TransponMatr[i][j] << "  ";
            }
            fout << '\n';
        }

        fout << "Союзная матрица:\n\n";
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                fout << AlliedMatr[i][j] << "  ";
            }
            fout << '\n';
        }

        fout << "Инверсная матрица:\n\n";
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                fout << InverseMatr[i][j] << "  ";
            }
            fout << '\n';
        }

        fout.close();
        std::cout << "Результаты вычеслений записаны в файл\n";
    }
    catch (MatrixException Exc)
    {
        std::cout << Exc.Error() << "\n\n";
    }
    
    return 0;
}

int SaveToFileMatrixMul(double** Matr1, double** Matr2, double** ResultMatr, int rows1, int cols1, int rows2, int cols2)
{
    std::ofstream fout("resultsMul.txt", std::ios::app);
    try
    {
        if (!fout.is_open())
            throw MatrixException(10);

        fout << "Результаты:\n\n"
            << "Введенные матрицы:\n\n";
        for (int i = 0; i < rows1; i++)
        {
            for (int j = 0; j < cols1; j++)
            {
                fout << Matr1[i][j] << "  ";
            }
            fout << '\n';
        }

        fout << "\n\n";

        for (int i = 0; i < rows2; i++)
        {
            for (int j = 0; j < cols2; j++)
            {
                fout << Matr2[i][j] << "  ";
            }
            fout << '\n';
        }

        fout << "\n\n";

        fout << "Результат умножения:\n\n";
        for (int i = 0; i < rows1; i++)
        {
            for (int j = 0; j < cols2; j++)
            {
                fout << ResultMatr[i][j] << "  ";
            }
            fout << '\n';
        }
        
        fout << "\n\n";
       
        fout.close();
        std::cout << "Результаты вычеслений записаны в файл\n";
    }
    catch (MatrixException Exc)
    {
        std::cout << Exc.Error() << "\n\n";
    }

    return 0;
}

int SaveToFileMatrixAddSub(double** Matr1, double** Matr2, double** ResultMatr, int rows, int cols)
{
    std::ofstream fout("resultsAddSub.txt", std::ios::app);
    try
    {
        if (!fout.is_open())
            throw MatrixException(10);

        fout << "Результаты:\n\n"
            << "Введенные матрица:\n\n";
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                fout << Matr1[i][j] << "  ";
            }
            fout << '\n';
        }

        fout << "\n\n";

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                fout << Matr2[i][j] << "  ";
            }
            fout << '\n';
        }

        fout << "\n\n";

        fout << "Результат математической операции:\n\n";
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                fout << ResultMatr[i][j] << "  ";
            }
            fout << '\n';
        }

        fout << "\n\n";

        fout.close();
        std::cout << "Результаты вычеслений записаны в файл\n";
    }
    catch (MatrixException Exc)
    {
        std::cout << Exc.Error() << "\n\n";
    }

    return 0;
}

int CorrectionInput(double** Matrix, int rows, int cols)
{
    double element = 0;
    int choice = 0;
    int row = -1, col = -1;

    std::cout << "Корректировать введенные данные?\n"
              << "[1] - для исправления введенных данных\n"
              << "[Любая другая цифра] - для продолжения вычислений\n"
              << "Выбор: ";

    std::cin >> choice;
    std::cout << "\n\n";
    if (std::cin.fail() != 0) {
        std::cin.clear();
    }
    if (choice == 1) {
        try {
            std::cout << "Введите номер СТРОКИ исправляемого элемента: ";
            std::cin >> row;
            if ((std::cin.fail() != 0) || (row < 1 || row > rows)) {
                std::cin.clear();
                throw MatrixException(13);
            }
            std::cout << "Введите номер СТОЛБЦА исправляемого элемента: ";
            std::cin >> col;
            if ((std::cin.fail() != 0) || (col < 1 || col > cols)) {
                std::cin.clear();
                throw MatrixException(14);
            }
            std::cout << "[" << row << "," << col << "] " << Matrix[row - 1][col - 1] << " --> ";
            std::cin >> element;
            std::cout << std::endl;
            if (std::cin.fail() != 0) {
                std::cin.clear();
                throw MatrixException(9);
            }
            Matrix[row - 1][col - 1] = element;
        }
        catch (MatrixException Exc) {
            std::cout << Exc.Error() << "\n\n";
        }
    }
    else {
        return -1;
    }
    return 0;
}
