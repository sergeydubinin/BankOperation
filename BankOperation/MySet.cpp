#include <algorithm>
#include <string>
#include <stdexcept>
#include <iterator>
#include <iostream>
#include <utility>
#include <type_traits>

template <typename T, typename Compare = std::greater<T>>
class MySet
{
public:
	MySet(std::size_t pc = 10) : m_cap(pc), m_size(0), m_data(m_cap ? new T[m_cap]() : nullptr) { }

	MySet(const MySet& other) = delete;
	MySet(MySet&& other) = delete;
	MySet& operator=(const MySet& other) = delete;
	MySet& operator=(MySet&& other) = delete;

	bool operator == (const MySet& obj) const
	{
		if (m_size != obj.getSize())
		{
			return false;
		}
		return std::equal(m_data, m_data + m_size, obj.m_data);
	}

	bool operator != (const MySet& obj) const
	{
		return !(*this == obj);
	}

	T& operator[](const std::size_t index)
	{
		if (index >= m_size && m_size != 0)
			throw std::out_of_range("index out of range " + std::to_string(index) + " >= " + std::to_string(m_size));
		else
			return m_data[index];
	}

	bool Add(const T& val)
	{
		auto el = val;
		std::size_t i = 0;
		for (; i < m_size; i++)
		{
			T val = m_data[i];
			if (Compare{}(val, el))
			{
				break;
			}

			if (!Compare{}(val, el) && !Compare{}(el, val))
			{
				return false;
			}
		}
		
		if (m_size < m_cap)
		{
			m_size++;
			for (; i < m_size; i++)
			{
				std::swap(el, m_data[i]);
			}
			return true;
		}

		T* newarr = new T[m_cap * 2]();
		m_cap = m_cap * 2;
		newarr[m_size] = el;
		std::copy(m_data, m_data + m_size, newarr);
		m_size++;
		delete[] m_data;
		m_data = newarr

		for (; i < m_size; i++)
		{
			std::swap(el, m_data[i]);
		}
		return true;
	}

	bool Add(T* el)
	{
		std::size_t i = 0;
		for (; i < m_size; i++)
		{
			auto val = m_data[i];
			if (Compare{}(val, el))
			{
				break;
			}

			if (!Compare{}(*val, *el) && !Compare{}(*el, *val))
			{
				return false;
			}
		}

		if (m_size < m_cap)
		{
			m_size++;
			for (; i < m_size; i++)
			{
				std::swap(el, m_data[i]);
			}
			return true;
		}

		T* newarr = new T[m_cap * 2]();
		m_cap = m_cap * 2;
		newarr[m_size] = el;
		std::copy(m_data, m_data + m_size, newarr);
		m_size++;
		delete[] m_data;
		m_data = newarr;

		for (; i < m_size; i++)
		{
			std::swap(el, m_data[i]);
		}
		return true;
	}

	template<typename Func>
	void Erase_if(Func f)
	{
		for (std::size_t i = 0; i < m_size; i++)
		{
			if (f(m_data[i]))
			{
				delete m_data[i];
				m_data[i] = nullptr;
				for (std::size_t j = i + 1; j < m_size; j++)
				{
					std::swap(m_data[j], m_data[i]);
				}
				m_size--;
				return;
			}
		}
	}

	std::size_t getSize() const
	{
		return m_size;
	}

	std::size_t getCapacity() const
	{
		return m_cap;
	}

	void clear()
	{
		free(std::is_pointer<T>{});
		m_size = 0;
	}

	private:
		void free(std::true_type)
		{
			for (std::size_t i = 0; i < m_size; i++)
			{
				delete m_data[i];
			}
		}

		void free(std::false_type)
		{
		}

		std::size_t m_cap;
		std::size_t m_size;
		T* m_data;
};