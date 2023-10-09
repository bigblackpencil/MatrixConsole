#pragma once
#ifndef FUNCTION_H
#define FUNCTION_H

void AboutProgram();
int MenuSelect(int* count);
void ClearConsole();
double** AllocMemmorySqMatrix(int size);
double** AllocMemmoryMatrix(int rows, int cols);
void FreeMemmorySqMatrix(double** SqMatrix, int size);
void PrintSqMatrix(double** Matrix, int rows, int cols);
double** MultipByNumber(double** Matrix, int size, double value);
double** Transposition(double** Matrix, int rows, int cols);
double Determinant(double** SqMatrix, int size);
double** AlliedMatrix(double** SqMatrix, int size);
double** InverseMatrix(double** SqMatrix, int size);
void MenuTypeOutput();
double** MultipMatrrixes(double** Matrix1, double** Matrix2, int row1, int cols1, int cols2);
void EnterFromKeyboard();
void EnterFromKeyboardForMul();
double** AddSubMatrices(double** Matrix1, double** Matrix2, int rows, int cols, int addsub);
void EnterFromKeyboardForAddorSub(short addsub);
void SqMatrixFromBinaryFile();
int CorrectionInput(double** Matrix, int rows, int cols);
int SaveToFileSqMatrix(double determinant, double** SqMatr, double** TransponMatr, double** AlliedMatr, double** InverseMatr, int size);
int SaveToFileMatrixMul(double** Matr1, double** Matr2, double** ResultMatr, int rows1, int cols1, int rows2, int cols2);
int SaveToFileMatrixAddSub(double** Matr1, double** Matr2, double** ResultMatr, int rows, int cols);

#endif
