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
	CurrencyType getCached() const { return m_cached; };
	virtual std::string toString() = 0;

protected:
	CurrencyType m_sum; //����� ������
	CurrencyType m_cached;
	std::tm m_dateStart; //���� �������� ������
	std::tm m_dateLastOp; //���� ��������� �������� � �������
	double m_percent; //������� ���������� �� ������
	unsigned long m_id;
};

//������� �����
class UsualDeposit : public Deposit
{
public:
	UsualDeposit(unsigned long id = 0, CurrencyType sum = CurrencyType(), std::tm date = std::tm(), double percent = 0);
	UsualDeposit(const std::string& str);
	virtual CurrencyType getSum() const { return m_sum; };
	virtual void setSum(CurrencyType value) { m_sum = value; };
	void print();
	std::string toString();
};

//������� �����
class TermDeposit : public Deposit
{
public:
	TermDeposit(unsigned long id = 0, CurrencyType sum = CurrencyType(), std::tm date = std::tm(), double percent = 0, 
		std::tm expdate = std::tm());
	TermDeposit(const std::string& str);
	virtual CurrencyType getSum() const { return m_sum; };
	virtual void setSum(CurrencyType value) { throw std::logic_error("TermDeposit called setSum"); };
	virtual void updateSum(double value, std::tm date) { throw std::logic_error("TermDeposit called updateSum"); };
	std::tm getExpirationDate() const { return m_dateExpiration; };
	void print();
	virtual CurrencyType calculateProfit(std::tm date);
	std::string toString();

private:
	std::tm m_dateExpiration; //���� ��������
};

//�������� �����
class CurrencyDeposit : public Deposit
{
public:
	CurrencyDeposit(unsigned long id = 0, CurrencyType sum = CurrencyType(), std::tm date = std::tm(), double percent = 0, 
		std::string cur = "USD", double rate = 1);
	CurrencyDeposit(const std::string& str);
	virtual CurrencyType getSum() const { return m_sum; };
	virtual void setSum(CurrencyType value) { m_sum = value; };
	std::string getCurrency() const { return m_cur; };
	double getExchangeRate() const { return m_rate; };
	void setExchangeRate(double value) { m_rate = value; };
	void print();
	CurrencyType getRubSum() const { return m_rate * m_sum; };
	CurrencyType fromRub(CurrencyType value) { return value / m_rate; };
	std::string toString();

private:
	std::string m_cur; //�������� ������
	double m_rate; //���� ������
};

