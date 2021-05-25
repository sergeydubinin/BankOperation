#define _CRT_SECURE_NO_WARNINGS
#include "Bank.h"
#include <iostream>
#include <sstream>

std::tm get_current_date()
{
	//������� �����
	auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::tm now_tm = *std::localtime(&now);
	return now_tm;
}

void Bank::OpenAccount()
{
	int code;
	std::cout << "������� 1 ��� �������� ������\t2 ��� ��������\t����� - ���������\n";
	std::cin >> code;
	if (code == 1)
	{
		unsigned long id;
		CurrencyType sum;
		std::tm date{};
		std::string d;
		double percent;
		std::cout << "������� id:";
		std::cin >> id;
		std::cout << "������� ����� ������:";
		std::cin >> sum;
		std::cout << "������� ������� ������������ ����������:";
		std::cin >> percent;
		std::cout << "������� ���� �������� � ������� yyyy-mm-dd:";
		std::cin >> d;
		std::istringstream ss(d);
		ss >> std::get_time(&date, "%Y-%m-%d");
		if (ss.fail())
		{
			return;
		}
		m_data.Add(new UsualDeposit(id, sum, date, percent));
		std::cout << "������ ���������\n";
		std::cin.get();
	}
	else if (code == 2)
	{
		unsigned long id;
		CurrencyType sum;
		std::tm date{}, expDate{};
		std::string d;
		double percent;
		std::cout << "������� id:";
		std::cin >> id;
		std::cout << "������� ����� ������:";
		std::cin >> sum;
		std::cout << "������� ������� ������������ ����������:";
		std::cin >> percent;
		std::cout << "������� ���� �������� � ������� yyyy-mm-dd:";
		std::cin >> d;
		std::istringstream ss(d);
		ss >> std::get_time(&date, "%Y-%m-%d");
		if (ss.fail())
		{
			return;
		}
		ss.clear();
		std::cout << "������� ���� ��������� � ������� yyyy-mm-dd:";
		std::cin >> d;
		ss.str(d);
		ss >> std::get_time(&expDate, "%Y-%m-%d");
		if (ss.fail())
		{
			return;
		}
		m_data.Add(new TermDeposit(id, sum, date, percent, expDate));
		std::cout << "������ ���������\n";
		std::cin.get();
	}
	else
	{
		unsigned long id;
		CurrencyType sum;
		std::tm date{};
		std::string d, c;
		double percent, rate;
		std::cout << "������� id:";
		std::cin >> id;
		std::cout << "������� ����� ������:";
		std::cin >> sum;
		std::cout << "������� ������� ������������ ����������:";
		std::cin >> percent;
		std::cout << "������� ���� �������� � ������� yyyy-mm-dd:";
		std::cin >> d;
		std::istringstream ss(d);
		ss >> std::get_time(&date, "%Y-%m-%d");
		if (ss.fail())
		{
			return;
		}
		ss.clear();
		std::cout << "������� ������:";
		std::cin >> c;
		std::cout << "������� ����:";
		std::cin >> rate;
		m_data.Add(new CurrencyDeposit(id, sum, date, percent, c, rate));
		std::cout << "������ ���������\n";
		std::cin.get();
	}
}

void Bank::ShowInfo()
{
	unsigned long id;
	std::cout << "������� id:";
	std::cin >> id;
	auto dep = m_data.getByID(id);
	if (dep != nullptr)
	{
		std::cout << "�� �����:" << dep->getSum() << '\n';
		std::cout << "��������� ���������:" << dep->calculateProfit(get_current_date()) << '\n';
	}
	else
	{
		std::cout << "���� � id = " << id << " �� ������\n";
	}
	std::cin.get();
}

void Bank::CloseAccount()
{
	unsigned long id;
	std::cout << "������� id:";
	std::cin >> id;
	auto dep = m_data.getByID(id);
	if (dep != nullptr)
	{
		std::cout << "����������:" << dep->getSum() + dep->calculateProfit(get_current_date()) << '\n';
		m_data.removeByID(id);
	}
	else
	{
		std::cout << "���� � id = " << id << " �� ������\n";
	}
	std::cin.get();

}

void Bank::EditAccount()
{
	unsigned long id;
	std::cout << "������� id:";
	std::cin >> id;
	auto dep = m_data.getByID(id);
	if (dep == nullptr)
	{
		std::cout << "���� � id = " << id << " �� ������\n";
		return;
	}

	//���� ����� �������, �� ��� ������ ��������������
	auto ptr = dynamic_cast<TermDeposit*>(dep);
	if (ptr != nullptr)
	{
		std::cout << "�� �� ������ ������������� ������� �����\n";
		return;
	}

	int code;
	std::tm date{};
	std::string d;
	CurrencyType sum;
	std::cout << "������� 1 ��� ���������� ������\t2 ��� ������\t����� - ������ ���������\n";
	std::cin >> code;
	if (code == 1)
	{
		std::cout << "������� ���� ��������� � ������� yyyy-mm-dd:";
		std::cin >> d;
		std::istringstream ss(d);
		ss >> std::get_time(&date, "%Y-%m-%d");
		if (ss.fail())
		{
			return;
		}
		ss.clear();
		std::cout << "������� �����:";
		std::cin >> sum;
		dep->updateSum(sum, date);
		std::cout << "������ ��������\n";
	}
	else if (code == 2)
	{
		std::cout << "������� ���� ������ � ������� yyyy-mm-dd:";
		std::cin >> d;
		std::istringstream ss(d);
		ss >> std::get_time(&date, "%Y-%m-%d");
		if (ss.fail())
		{
			return;
		}
		ss.clear();
		std::cout << "������� �����:";
		std::cin >> sum;
		dep->updateSum(-sum, date);
		std::cout << "������ ��������\n";
	}
	else
	{
		auto date = get_current_date();
		std::cout << "����������: " << dep->calculateProfit(date) << " ���������\n";
		dep->setLastOpDate(date);
	}
	std::cin.get();
}

void Bank::LoadFromFile(const std::string& fileName)
{
	m_data.LoadFromFile(fileName);
}

void Bank::SaveToFile(const std::string& fileName)
{
	m_data.SaveToFile(fileName);
}