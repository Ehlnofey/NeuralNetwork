#pragma once
/*
**Gère un tableau de taille size en mémoire. 
*/
template <typename T>
class Matrix
{
public:
	Matrix():m_firstElem(NULL)
	{
		m_lastElem = m_firstElem;
	}

	Matrix(unsigned int size) :m_firstElem(new T[size]())
	{
		m_lastElem = m_firstElem + size - 1;
	}

	Matrix(const Matrix<T> &copy) :m_firstElem(NULL)
	{
		m_lastElem = m_firstElem;

		if (copy.m_firstElem != NULL)
		{
			m_firstElem = new T[copy.m_lastElem - copy.m_firstElem + 1]();

			for (unsigned int i = 0; i < copy.m_lastElem - copy.m_firstElem + 1; i++)
				m_firstElem[i] = copy.m_firstElem[i];

			size_t delta = copy.m_lastElem - copy.m_firstElem;

			m_lastElem = m_firstElem + delta;
		}
	}

	Matrix& operator=(const Matrix &m)
	{
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

	virtual void init(unsigned int size)
	{
		if (m_firstElem != NULL)
			delete m_firstElem;

		m_firstElem = new T[size]();

		m_lastElem = m_firstElem + size - 1;
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

	template <typename F>
	void apply(F& f)
	{
		for (T* ptr = m_firstElem;ptr <= m_lastElem;ptr++)
			f(*ptr);
	}

	template <typename F>
	void apply(F* f)
	{
		for (T* ptr = m_firstElem;ptr <= m_lastElem;ptr++)
			(*f)(*ptr);
	}

	virtual T& operator[](unsigned int index)
	{
		if (index < 0 || index >= length())
			throw std::exception("Bah index in a Matrix.");

		return m_firstElem[index];
	}

	virtual ~Matrix()
	{
		if (m_firstElem != NULL)
			delete m_firstElem;

		m_firstElem = NULL;
	}

protected:

	T* m_firstElem;
	T* m_lastElem;
};

