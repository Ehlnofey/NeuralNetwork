#pragma once
#include <cstdarg>
#include <cmath>
#include "Matrix.h"

template <typename T>
class MatrixCoord : public Matrix<T>
{
public:
	MatrixCoord(unsigned int size, ...) : Matrix<T>(size)
	{
		va_list vl;
		va_start(vl, size);
		
		for (unsigned int i = 0; i < size; i++)
			m_firstElem[i] = va_arg(vl, unsigned int);

		va_end(vl);
	}/*
	MatrixCoord(unsigned int size) : Matrix<T>(size)
	{

	}*/

	MatrixCoord():Matrix<T>()
	{

	}

	__int64 size()
	{
		return length();
	}

	~MatrixCoord()
	{
	}

private:

};