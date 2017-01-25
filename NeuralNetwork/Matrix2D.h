#pragma once
#include "Matrix.h"

template <typename T>
class Matrix2D :
	public Matrix<T>
{
public:
	Matrix2D() :Matrix<T>(),m_n(0),m_m(0)
	{

	}

	Matrix2D(unsigned int n,unsigned int m) : Matrix<T>(n*m),m_n(n),m_m(m)
	{

	}

	Matrix2D(std::vector<T> &v) : Matrix<T>((unsigned int)v.size()),m_n((unsigned int)v.size()),m_m(1)
	{
		for (unsigned int i = 0; i < v.size(); i++)
			m_firstElem[i] = v[i];
	}

	Matrix2D& operator=(const Matrix2D &m) 
	{
		m_n = m.m_n;
		m_m = m.m_m;

		unsigned int mlength = unsigned int(m.m_lastElem - m.m_firstElem + 1);
		if (mlength == length())
		{
			for (unsigned int i = 0; i < mlength; i++)
				m_firstElem[i] = m.m_firstElem[i];
		}
		else
		{
			if (m_firstElem != NULL)
				delete m_firstElem;

			m_firstElem = new T[m.m_lastElem - m.m_firstElem + 1]();

			for (unsigned int i = 0; i < m.m_lastElem - m.m_firstElem + 1; i++)
				m_firstElem[i] = m.m_firstElem[i];

			size_t delta = m.m_lastElem - m.m_firstElem;

			m_lastElem = m_firstElem + delta;
		}

		return *this;
	}
	operator std::vector<T>()
	{
		std::vector<T> v(length());

		for (unsigned int i = 0; i < v.size(); i++)
			v[i] = m_firstElem[i];

		return v;
	}

	Matrix2D transp()
	{
		Matrix2D t(m_m, m_n);

		for (unsigned int i = 0; i < m_n; i++)
			for (unsigned int j = 0; j < m_m; j++)
				t.m_firstElem[i*t.m_n+j]= m_firstElem[j*m_n + i];

		return t;
	}

	Matrix2D& operator+=(Matrix2D &m2)
	{
		if (m_m != m2.m() || m_n != m2.n())
			throw std::exception("Dim of Matrix2D incompatible.");

		for (unsigned int i = 0; i < m_n; i++)
			for (unsigned int j = 0; j < m_m; j++)
				m_firstElem[j*m_n + i] += m2(i, j);

		return *this;
	}
	Matrix2D& operator/=(T m2)
	{
		for (unsigned int i = 0; i < m_n; i++)
			for (unsigned int j = 0; j < m_m; j++)
				m_firstElem[j*m_n + i] /= m2;

		return *this;
	}
	Matrix2D& operator*=(T m2)
	{
		for (unsigned int i = 0; i < m_n; i++)
			for (unsigned int j = 0; j < m_m; j++)
				m_firstElem[j*m_n + i] *= m2;

		return *this;
	}

	virtual void init2D(unsigned int n, unsigned int m)
	{
		init(n*m);
		m_n = n;
		m_m = m;
	}

	T& operator()(unsigned int i, unsigned int j)
	{
		if (m_firstElem + j*m_n + i > m_lastElem)
			throw std::exception("Out of range in Matrix2D");
		return m_firstElem[j*m_n+i];
	}

	const unsigned int& n()
	{
		return m_n;
	}

	const unsigned int& m()
	{
		return m_m;
	}

	virtual ~Matrix2D()
	{
		if(m_firstElem!=NULL)
			delete m_firstElem;

		m_firstElem = NULL;
	}

private :
	unsigned int m_n, m_m;
};

template <typename T>
Matrix2D<T> operator*(Matrix2D<T> &m1, Matrix2D<T> &m2)
{
	if (m1.m() != m2.n())
		throw std::exception("Dim of Matrix2D incompatible.");

	Matrix2D<T> res(m1.n(),m2.m());

	for (unsigned int i = 0; i < res.n(); i++)
		for (unsigned int j = 0; j < res.m(); j++)
			for (unsigned int k = 0; k < m1.m(); k++)
				res(i, j) += m1(i,k) * m2(k,j);

	return res;
}
template <typename T, typename S>
Matrix2D<T> operator*(S &m1, const Matrix2D<T> &m2)
{
	Matrix2D<T> res(m2);

	for (unsigned int i = 0; i < res.n(); i++)
		for (unsigned int j = 0; j < res.m(); j++)
			res(i, j) *= m1;

	return res;
}
template <typename T>
Matrix2D<T> operator+(Matrix2D<T> &m1, Matrix2D<T> &m2)
{
	if (m1.m() != m2.m() || m1.n() != m2.n())
		throw std::exception("Dim of Matrix2D incompatible.");

	Matrix2D<T> res(m1.n(), m1.m());

	for (unsigned int i = 0; i < res.n(); i++)
		for (unsigned int j = 0; j < res.m(); j++)
			res(i, j) = m1(i, j) + m2(i, j);

	return res;
}
template <typename T>
Matrix2D<T> operator-(Matrix2D<T> &m1, Matrix2D<T> &m2)
{
	if (m1.m() != m2.m() || m1.n() != m2.n())
		throw std::exception("Dim of Matrix2D incompatible.");

	Matrix2D<T> res(m1.n(), m1.m());

	for (unsigned int i = 0; i < res.n(); i++)
		for (unsigned int j = 0; j < res.m(); j++)
			res(i, j) = m1(i, j) - m2(i, j);

	return res;
}


template <typename T>
Matrix2D<T> hadamard(Matrix2D<T> &m1, Matrix2D<T> &m2)
{
	if (m1.m() != m2.m() || m1.n() != m2.n())
		throw std::exception("Dim of Matrix2D incompatible.");

	Matrix2D<T> res(m1.n(), m2.m());

	for (unsigned int i = 0; i < res.n(); i++)
		for (unsigned int j = 0; j < res.m(); j++)
			res(i, j) = m1(i, j)*m2(i, j);

	return res;
}