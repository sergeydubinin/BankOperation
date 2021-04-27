#pragma once

#include "Deposit.h"

const std::size_t Size = 100;

class Table
{
public:
	Table();
	std::size_t getCount() const { return m_count; };
	const Deposit* get(std::size_t i) const { return m_data[i]; };
	bool Add(Deposit* ptr);
	Deposit* getByID(unsigned long id);
	void removeByID(unsigned long id);
	void print() const;
	~Table();
private:
	Deposit* m_data[Size];
	std::size_t m_count;
};