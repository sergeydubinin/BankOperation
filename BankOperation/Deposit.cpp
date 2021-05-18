#include "Deposit.h"
#include <iostream>

Deposit::Deposit(unsigned long id, CurrencyType sum, std::tm date, double percent) : 
	m_sum(sum), m_dateStart(date), m_dateLastOp(date), m_percent(percent), m_id(id), m_cached(0) {}

bool Deposit::setLastOpDate(std::tm date)
{
	time_t cur = mktime(&date);
	time_t lastOp = mktime(&m_dateStart);
	if (cur == -1 || lastOp == -1 || cur < lastOp)
	{
		return false;
	}
	m_dateLastOp = date;
	return true;
}

CurrencyType Deposit::calculateProfit(std::tm date) const
{
	time_t cur = mktime(&date);
	auto dateLastOp = m_dateLastOp;
	time_t lastOp = mktime(&dateLastOp);
	if (cur == -1 || lastOp == -1 || cur < lastOp)
	{
		return m_cached;
	}

	int diff = static_cast<int>(difftime(cur, lastOp) / 2592000);
	auto temp = m_sum;
	for (int i = 0; i < diff; i++)
	{
		temp += m_percent * temp / 100;
	}
	return m_cached + (temp - m_sum);
}

void Deposit::updateSum(double value, std::tm date)
{
	auto profit = calculateProfit(date);
    if (value > 0 && setLastOpDate(date))
    {
        m_sum += value;
        m_cached += profit;
    }
    else if (std::abs(value) < m_sum && setLastOpDate(date))
    {
        m_sum += value;
        m_cached += profit;
    }
}

UsualDeposit::UsualDeposit(unsigned long id, CurrencyType sum, std::tm date, double percent) : 
	Deposit(id, sum, date, percent) {}

void UsualDeposit::print()
{
	std::cout << "������� �����\nID:" << getID() << "\nDate start:" << std::put_time(&m_dateStart, "%Y-%m-%d") <<
		"\nSum:" << m_sum << "\nPercent:" << m_percent << "\nLast operation:" <<
		std::put_time(&m_dateLastOp, "%Y-%m-%d") << '\n';
}

TermDeposit::TermDeposit(unsigned long id, CurrencyType sum, std::tm date, double percent, 
	std::tm expdate) : Deposit(id, sum, date, percent), m_dateExpiration(expdate) {}

void TermDeposit::print()
{
	std::cout << "������� �����\nID:" << getID() << "\nDate start:" << std::put_time(&m_dateStart, "%Y-%m-%d") <<
		"\nSum:" << m_sum << "\nPercent:" << m_percent <<
		"\nExpirationDate:" << std::put_time(&m_dateExpiration, "%Y-%m-%d") <<
		"\nLast operation:" << std::put_time(&m_dateLastOp, "%Y-%m-%d") << '\n';
}
CurrencyType TermDeposit::calculateProfit(std::tm date)
{
	time_t cur = mktime(&date);
	time_t lastOp = mktime(&m_dateLastOp);

	if (cur == -1 || lastOp == -1 || cur < lastOp)
	{
		return CurrencyType();
	}

	time_t expDate = mktime(&m_dateExpiration);
	if (cur > expDate)
	{
		cur = expDate;
	}

	int diff = static_cast<int>(difftime(cur, lastOp) / 2592000);
	auto temp = m_sum;
	for (int i = 0; i < diff; i++)
	{
		temp += m_percent * temp / 100;
	}
	return temp - m_sum;
}

CurrencyDeposit::CurrencyDeposit(unsigned long id, CurrencyType sum, std::tm date, double percent, 
	std::string cur, double rate) : Deposit(id, sum, date, percent), m_cur(cur), m_rate(rate) {}

void CurrencyDeposit::print()
{
	std::cout << "�������� �����\nID:" << getID() << "\nDate start:" << std::put_time(&m_dateStart, "%Y-%m-%d") <<
		"\nSum:" << m_sum << "\nPercent:" << m_percent <<
		"\nCurrency:" << m_cur << "\nExchange rate:" << m_rate <<
		"\nLast operation:" << std::put_time(&m_dateLastOp, "%Y-%m-%d") << '\n';
}
