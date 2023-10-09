#pragma once
class MatrixException
{
private:
	int numError;
public:
	MatrixException(int i);
	const char* Error() const;
};

