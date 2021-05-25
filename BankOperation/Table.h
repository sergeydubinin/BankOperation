#pragma once

#include "Deposit.h"
#include <set>

class Table
{
public:
	Table() {};
	std::size_t getCount() const { return m_data.size(); };
	bool Add(Deposit* ptr);
	Deposit* getByID(unsigned long id);
	void removeByID(unsigned long id);
	void print() const;
	void LoadFromFile(const std::string& fileName);
	void SaveToFile(const std::string& fileName);
	~Table();

	Table(const Table& other) = delete;
	Table(Table&& other) = delete;
	Table& operator=(const Table& other) = delete;
	Table& operator=(Table&& other) = delete;

private:
	struct DepositCMP
	{
		bool operator()(const Deposit* a, const Deposit* b) const
		{
			return a->getID() < b->getID();
		}
	};

	std::set<Deposit*, DepositCMP> m_data;
};