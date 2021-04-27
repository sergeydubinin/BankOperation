#include "Table.h"
#include <iostream>

Table::Table() : m_count(0)
{
	for (std::size_t i = 0; i < Size; i++)
	{
		m_data[i] = nullptr;
	}
}

bool Table::Add(Deposit* ptr)
{
	if (m_count == Size)
	{
		return false;
	}
	std::size_t i = 0;
	for (; i < Size; i++)
	{
		if (m_data[i] == nullptr || m_data[i]->getID() > ptr->getID())
		{
			break;
		}

		if (m_data[i] != nullptr && m_data[i]->getID() == ptr->getID())
		{
			return false; //уже существует
		}
	}
	m_count++;
	if (m_data[i] == nullptr)
	{
		m_data[i] = ptr;
		return true;
	}
	//сдвигаем
	for (; i < Size; i++)
	{
		std::swap(ptr, m_data[i]);
	}
	return true;
}

Deposit* Table::getByID(unsigned long id)
{
	for (std::size_t i = 0; i < Size; i++)
	{
		if (m_data[i] != nullptr && m_data[i]->getID() == id)
		{
			return m_data[i];
		}
	}
	return nullptr;
}

void Table::removeByID(unsigned long id)
{
	for (std::size_t i = 0; i < Size; i++)
	{
		if (m_data[i] != nullptr && m_data[i]->getID() == id)
		{
			delete m_data[i];
			m_count--;
			m_data[i] = nullptr;
			for (std::size_t j = i + 1; j < Size; j++)
			{
				std::swap(m_data[j], m_data[i]);
			}
			return;
		}
	}
}

void Table::print() const
{
	for (std::size_t i = 0; i < Size; i++)
	{
		if (m_data[i] != nullptr)
		{
			m_data[i]->print();
			std::cout << "\n\n";
		}
	}
}

Table::~Table()
{
	for (std::size_t i = 0; i < Size; i++)
	{
		delete m_data[i];
	}
}

