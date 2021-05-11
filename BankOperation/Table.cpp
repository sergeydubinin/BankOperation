#include "Table.h"
#include <iostream>

bool Table::Add(Deposit* ptr)
{
	auto it = m_data.find(ptr);
	if (it != m_data.end())
	{
		return false;
	}
	m_data.insert(ptr);
	return true;
}

Deposit* Table::getByID(unsigned long id)
{
	for (const auto& ptr : m_data)
	{
		if (ptr->getID() == id)
		{
			return ptr;
		}
	}
	return nullptr;
}

void Table::removeByID(unsigned long id)
{
	for (const auto& ptr : m_data)
	{
		if (ptr->getID() == id)
		{
			m_data.erase(ptr);
			return;
		}
	}
}

void Table::print() const
{
	for (const auto& ptr : m_data)
	{
		ptr->print();
		std::cout << "\n\n";
	}
}

