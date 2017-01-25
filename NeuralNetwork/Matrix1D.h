#pragma once
#include "Matrix.h"

template <typename T>
class Matrix1D :
	public Matrix<T>
{
public:
	Matrix1D():Matrix<T>(NULL)
	{

	}

	Matrix1D(unsigned int size) : Matrix<T>(size)
	{

	}


	~Matrix1D()
	{

	}
};

template <typename T>
T operator*(const Matrix1D<T> &m1, const Matrix1D<T> &m2)
{
	T res(0);

	for (unsigned int i = 0; i < m1.length(); i++)
		res += m1[i] * m2[i];

	return res;
}
template <typename T,F>
T operator*(const Matrix1D<T> &m1, const Matrix1D<T> &m2, T& init, F& f)
{
	T res(init);

	for (unsigned int i = 0; i < m1.length(); i++)
		res += f(m1[i], m2[i]);

	return res;
}