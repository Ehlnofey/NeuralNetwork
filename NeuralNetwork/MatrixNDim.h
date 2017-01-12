#pragma once
#include <cstdarg>
#include <cmath>

class MatrixCoord
{
public:
	MatrixCoord(unsigned int size, ...) : m_size(size)
	{
		va_list vl;
		va_start(vl, m_size);

		m_coord = new unsigned int[m_size]();

		for (unsigned int i = 0; i < m_size; i++)
			m_coord[i] = va_arg(vl, unsigned int);

		va_end(vl);
	}

	MatrixCoord(const MatrixCoord &copy) : m_coord(new unsigned int[copy.m_size]()),m_size(copy.m_size)
	{
		for (unsigned int i = 0; i < m_size; i++)
			m_coord[i] = copy.m_coord[i];
	}

	MatrixCoord() :m_size(0), m_coord(NULL)
	{

	}

	void init(unsigned int size)
	{
		m_size = size;

		if (m_coord != NULL)
			delete m_coord;

		m_coord = new unsigned int[m_size]();
	}

	unsigned int size()
	{
		return m_size;
	}

	unsigned int& operator[](unsigned int index)
	{
		if (index < 0 || index >= m_size)
			throw std::exception("Bah index in MatrixCoord.");

		return m_coord[index];
	}

	~MatrixCoord()
	{
		if (m_coord != NULL)
			delete m_coord;
	}

private:

	unsigned int* m_coord;
	unsigned int m_size;
};

template <typename T>
class MatrixNDim
{
public:
	MatrixNDim(unsigned int dim, unsigned int size, T elemType) : m_n(dim),m_size(size),m_firstElem(NULL),m_lastElem(NULL)
	{
		unsigned int tot(unsigned int(std::pow(m_size, m_n)));
		m_firstElem = new T[tot]();

		for (unsigned int i = 0;i < tot;i++)
			m_firstElem[i] = elemType;

		m_lastElem = m_firstElem + tot - 1;
	}
	MatrixNDim(unsigned int dim, unsigned int size) : m_n(dim), m_size(size), m_firstElem(NULL), m_lastElem(NULL)
	{
		unsigned int tot(unsigned int(std::pow(m_size, m_n)));
		m_firstElem = new T[tot]();
		m_lastElem = m_firstElem + tot - 1;
	}
	T& operator[](unsigned int i)
	{
		if (m_firstElem + i > m_lastElem)
			throw std::exception("Out of range in a MatrixNDim.");
		return m_firstElem[i];
	}

	template <typename F>
	void apply(F& f)
	{
		for (T* ptr= m_firstElem;ptr <= m_lastElem;ptr++)
			f(*ptr);
	}

	template <typename F>
	void apply(F* f)
	{
		for (T* ptr = m_firstElem;ptr <= m_lastElem;ptr++)
			(*f)(*ptr);
	}
	template <typename F>
	void applyForEachCoord(F& f)
	{
		for (T* ptr = m_firstElem;ptr <= m_lastElem;ptr++)
			f(*ptr, getDimCoord(unsigned int(ptr - m_firstElem)));
	}

	MatrixCoord getDimCoord(unsigned int index)
	{
		MatrixCoord coord;

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

	__int64 length()
	{
		return m_lastElem - m_firstElem + 1;
	}

	T& first()
	{
		return *m_firstElem;
	}

	T& last()
	{
		return *m_lastElem;
	}

	~MatrixNDim()
	{
		delete m_firstElem;
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
	T* m_firstElem;
	T* m_lastElem;
};
