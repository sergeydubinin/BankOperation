#include "Table.h"
#include <iostream>
#include <fstream>

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
	for (auto& ptr : m_data)
	{
		if (ptr->getID() == id)
		{
			delete ptr;
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

Table::~Table()
{
	for (const auto& ptr : m_data)
	{
		delete ptr;
	}
}

void Table::LoadFromFile(const std::string& fileName)
{
	std::ifstream in(fileName);
	std::string line;
	m_data.clear();
	while (std::getline(in, line))
	{
		if (line.empty())
		{
			continue;
		}
		auto pos = line.find_first_of(';');
		auto code = line.substr(0, pos);
		auto str = line.substr(pos + 1);
		if (code == "1")
		{
			Add(new UsualDeposit(str));
		}
		else if (code == "2")
		{
			Add(new TermDeposit(str));
		}
		else if (code == "3")
		{
			Add(new CurrencyDeposit(str));
		}
	}
}

void Table::SaveToFile(const std::string& fileName)
{
	std::ofstream out(fileName);
	for (const auto& ptr : m_data)
	{
		out << ptr->toString() << '\n';
	}
}