#pragma once
#include <cstdarg>
#include <cmath>
#include "Matrix.h"
#include "MatrixCoord.h"

template <typename T>
class MatrixNDim : public Matrix<T>
{
public:
	MatrixNDim(unsigned int dim, unsigned int size, T elemType) : m_n(dim),m_size(size), Matrix<T>()
	{
		unsigned int tot(unsigned int(std::pow(m_size, m_n)));
		
		this->init(tot);

		for (unsigned int i = 0;i < tot;i++)
			m_firstElem[i] = elemType;
	}
	MatrixNDim(unsigned int dim, unsigned int size) : m_n(dim), m_size(size)
	{
		unsigned int tot(unsigned int(std::pow(m_size, m_n)));
		this->init(tot);
	}

	template <typename F>
	void applyForEachCoord(F& f)
	{
		for (T* ptr = m_firstElem;ptr <= m_lastElem;ptr++)
			f(*ptr, getDimCoord(unsigned int(ptr - m_firstElem)));
	}

	MatrixCoord<unsigned int> getDimCoord(unsigned int index)
	{
		MatrixCoord<unsigned int> coord;

		coord.init(m_n);

		for (unsigned int i = 0;i < m_n;i++)
		{
			coord[i] = index%m_size;

			index /= m_n;
		}

		return coord;
	}


	T& operator()(...)
	{
		va_list vl;
		va_start(vl, m_n);

		unsigned int index(0);
		unsigned int N(1);

		for (unsigned int i = 0; i < m_n; i++) {
			index += va_arg(vl, unsigned int)*N;
			N *= m_size;
		}
		
		va_end(vl);

		if (m_firstElem + index > m_lastElem || index < 0)
			throw std::exception("Out of range in a MatrixNDim.");

		return m_firstElem[index];
	}
	template <typename S>//Renvoie une copie, ça me plait pas mais j'ai pas mieux. 
	MatrixNDim<T> getSubMatrix(S& coord)
	{
		unsigned int newDim(m_n-coord.size());

		MatrixNDim<T> sub(newDim,m_size);
		MatrixCoord<unsigned int> c(m_n),d(sub.dim());

		for (unsigned int i = 0; i < coord.size(); i++)
			c[i] = coord[i];

		while (c.last() < m_size)
		{
			for (unsigned int i = coord.size(); i < c.size() - 1; i++)
			{
				if (c[i] >= m_size)
				{
					c[i + 1]++;
					c[i] = 0;
				}
				d[i] = c[i];
			}

			d.last() = c.last();

			sub.get(d) = this.get(c);

			c[coord.size()]++;
		}

		return sub;
	}

	template <typename S>
	T& get(S& coord)
	{
		if (coord.size() != m_n)
		{
			throw std::exception("Bad coord in a MatrixNDim.");

			return *m_firstElem;
		}
		unsigned int index(0);
		unsigned int N(1);

		for (unsigned int i = 0; i < m_n; i++) {
			index += coord[i]*N;
			N *= m_size;
		}

		if (m_firstElem + index > m_lastElem || index < 0)
			throw std::exception("Out of range in a MatrixNDim.");

		return m_firstElem[index];
	}

	unsigned int dim()
	{
		return m_n;
	}

	unsigned int size()
	{
		return m_size;
	}

	~MatrixNDim()
	{
		
	}

private:
	
	T& get(unsigned int *coord)
	{
		unsigned int index(0);
		unsigned int N(1);

		for (unsigned int i = 0; i < m_n; i++) {
			index += coord[i] * N;
			N *= m_size;
		}

		if (m_firstElem + index > m_lastElem || index < 0)
			throw std::exception("Out of range in a MatrixNDim.");

		return m_firstElem[index];
	}

	unsigned int m_n;
	unsigned int m_size;
};
