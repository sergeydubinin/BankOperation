#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <chrono>

#include "Table.h"

std::tm get_current_date()
{
	//������� �����
	auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::tm now_tm = *std::localtime(&now);
	return now_tm;
}

int main(void)
{
	system("chcp 1251 && cls");
	Table t;
	std::tm d1{}, d2{}, d3{}, cur{}, d4{};
	std::istringstream ss("2010-2-1");
	ss >> std::get_time(&d1, "%Y-%m-%d");

	ss.clear();
	ss.str("2010-3-1");
	ss >> std::get_time(&d2, "%Y-%m-%d");

	ss.clear();
	ss.str("2011-3-1");
	ss >> std::get_time(&d4, "%Y-%m-%d");

	ss.clear();
	ss.str("2010-4-1");
	ss >> std::get_time(&d3, "%Y-%m-%d");

	ss.clear();
	ss.str("2010-4-25");
	ss >> std::get_time(&cur, "%Y-%m-%d");

	Deposit* a = new UsualDeposit(1, 2, d1, 3);
	Deposit* b = new TermDeposit(2, 3, d2, 7, d4);
	Deposit* c = new CurrencyDeposit(3, 4, d3);
	t.Add(b);
	t.Add(a);
	t.Add(c);
	do
	{
		std::cout << " 0. ������� ����� ����\n";
		std::cout << " 1. �������� ������� ��������� �����\n";
		std::cout << " 2. ������� ����\n";
		std::cout << " 3. �������� ��������� �����\n";
		std::cout << " 4. �������� ���������� �� ���� ������\n";
		std::cout << " 5. ������� �������\n";
		std::cout << "����� - �����\n";
		char ch = std::cin.get();
		std::cin.ignore(255, '\n');
		switch (ch)
		{
		case '0':
		{
			int code;
			std::cout << "������� 1 ��� �������� ������, 2 - ��� ��������, ����� - ���������\n";
			std::cin >> code;
			if (code == 1)
			{
				unsigned long id;
				CurrencyType sum;
				std::tm date{};
				std::string d;
				double percent;
				std::cout << "������� id: ";
				std::cin >> id;
				std::cout << "������� ����� ������: ";
				std::cin >> sum;
				std::cout << "������� ������� ������������ ����������: ";
				std::cin >> percent;
				std::cout << "������� ���� �������� � ������� yyyy-mm-dd: ";
				std::cin >> d;
				std::istringstream ss(d);
				ss >> std::get_time(&date, "%Y-%m-%d");
				if (ss.fail())
				{
					break;
				}
				t.Add(new UsualDeposit(id, sum, date, percent));
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
				std::cout << "������� id: ";
				std::cin >> id;
				std::cout << "������� ����� ������: ";
				std::cin >> sum;
				std::cout << "������� ������� ������������ ����������: ";
				std::cin >> percent;
				std::cout << "������� ���� �������� � ������� yyyy-mm-dd: ";
				std::cin >> d;
				std::istringstream ss(d);
				ss >> std::get_time(&date, "%Y-%m-%d");
				if (ss.fail())
				{
					break;
				}
				ss.clear();
				std::cout << "������� ���� ��������� ����� �������� � ������� yyyy-mm-dd: ";
				std::cin >> d;
				ss.str(d);
				ss >> std::get_time(&expDate, "%Y-%m-%d");
				if (ss.fail())
				{
					break;
				}
				t.Add(new TermDeposit(id, sum, date, percent, expDate));
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
				std::cout << "������� id: ";
				std::cin >> id;
				std::cout << "������� ����� ������: ";
				std::cin >> sum;
				std::cout << "������� ������� ������������ ����������: ";
				std::cin >> percent;
				std::cout << "������� ���� �������� � ������� yyyy-mm-dd: ";
				std::cin >> d;
				std::istringstream ss(d);
				ss >> std::get_time(&date, "%Y-%m-%d");
				if (ss.fail())
				{
					break;
				}
				ss.clear();
				std::cout << "������� ������: ";
				std::cin >> c;
				std::cout << "������� ����: ";
				std::cin >> rate;
				t.Add(new CurrencyDeposit(id, sum, date, percent, c, rate));
				std::cout << "������ ���������\n";
				std::cin.get();
			}

			break;
		}
		case '1':
		{
			unsigned long id;
			std::cout << "������� id: ";
			std::cin >> id;
			auto dep = t.getByID(id);
			if (dep != nullptr)
			{
				std::cout << "�� �����: " << dep->getSum() << '\n';
				std::cout << "��������� ���������: " << dep->calculateProfit(get_current_date()) << '\n';
			}
			else
			{
				std::cout << "���� � id = " << id << " �� ������\n";
			}
			std::cin.get();
			break;
		}
		case '2':
		{
			unsigned long id;
			std::cout << "������� id: ";
			std::cin >> id;
			auto dep = t.getByID(id);
			if (dep != nullptr)
			{
				std::cout << "����������: " << dep->getSum() + dep->calculateProfit(get_current_date()) << '\n';
				t.removeByID(id);
			}
			else
			{
				std::cout << "���� � id = " << id << " �� ������\n";
			}
			std::cin.get();
			break;
		}
		case '3':
		{
			unsigned long id;
			std::cout << "������� id: ";
			std::cin >> id;
			auto dep = t.getByID(id);
			if (dep == nullptr)
			{
				std::cout << "���� � id = " << id << " �� ������\n";
				break;
			}
			int code;
			CurrencyType sum;
			std::cout << "������� 1 ��� ���������� ������, 2 - ��� ������, ����� - ������ ���������\n";
			std::cin >> code;
			if (code == 1)
			{
				std::cout << "������� �����: ";
				std::cin >> sum;
				dep->updateSum(sum);
				std::cout << "������ ��������\n";
			}
			else if (code == 2)
			{
				std::cout << "������� �����: ";
				std::cin >> sum;
				dep->updateSum(-sum);
				std::cout << "������ ��������\n";
			}
			else
			{
				auto date = get_current_date();
				std::cout << "����������: " << dep->calculateProfit(date) << " ���������\n";
				dep->setLastOpDate(date);
			}
			std::cin.get();
			break;
		}
		case '4':
		{
			t.print();
			break;
		}
		case '5':
		{
			system("cls");
			break;
		}
		default:
		{
			std::cin.get();
			return 0;
		}
		}
	} while (true);
}
