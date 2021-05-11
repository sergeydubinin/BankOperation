#pragma once
#include <ctime>
#include <string>
#include <chrono>
#include <iomanip>

using CurrencyType = double;

class Deposit
{
public:
	Deposit(unsigned long id = 0, CurrencyType sum = CurrencyType(), std::tm date = std::tm(), double percent = 0);
	virtual ~Deposit() {};
	unsigned long getID() const { return m_id; };
	virtual CurrencyType getSum() const = 0;
	virtual void setSum(CurrencyType value) = 0;
	std::tm getDate() const { return m_dateStart; };
	std::tm getLastOpDate() const { return m_dateLastOp; };
	bool setLastOpDate(std::tm date);
	virtual void print() = 0;
	virtual CurrencyType calculateProfit(std::tm date) const;
	double getPercent() const { return m_percent; };
	virtual void updateSum(double value, std::tm date);

protected:
	CurrencyType m_sum; //Сумма вклада
	std::tm m_dateStart; //Дата открытия вклада
	std::tm m_dateLastOp; //Дата последней операции с вкладом
	double m_percent; //Процент начисления по вкладу

private:
	unsigned long m_id;
};

//Обычный вклад
class UsualDeposit : public Deposit
{
public:
	UsualDeposit(unsigned long id = 0, CurrencyType sum = CurrencyType(), std::tm date = std::tm(), double percent = 0);
	virtual CurrencyType getSum() const { return m_sum; };
	virtual void setSum(CurrencyType value) { m_sum = value; };
	void print();
};

//Срочный вклад
class TermDeposit : public Deposit
{
public:
	TermDeposit(unsigned long id = 0, CurrencyType sum = CurrencyType(), std::tm date = std::tm(), double percent = 0, 
		std::tm expdate = std::tm());
	virtual CurrencyType getSum() const { return m_sum; };
	virtual void setSum(CurrencyType value) {};
	virtual void updateSum(double value, std::tm date) {};
	std::tm getExpirationDate() const { return m_dateExpiration; };
	void print();
	virtual CurrencyType calculateProfit(std::tm date);

private:
	std::tm m_dateExpiration; //Срок хранения
};

//Валютный вклад
class CurrencyDeposit : public Deposit
{
public:
	CurrencyDeposit(unsigned long id = 0, CurrencyType sum = CurrencyType(), std::tm date = std::tm(), double percent = 0, 
		std::string cur = "USD", double rate = 1);
	virtual CurrencyType getSum() const { return m_sum; };
	virtual void setSum(CurrencyType value) { m_sum = value; };
	std::string getCurrency() const { return m_cur; };
	double getExchangeRate() const { return m_rate; };
	void setExchangeRate(double value) { m_rate = value; };
	void print();
	CurrencyType getRubSum() const { return m_rate * m_sum; };
	CurrencyType fromRub(CurrencyType value) { return value / m_rate; };

private:
	std::string m_cur; //Название валюты
	double m_rate; //Курс обмена
};

