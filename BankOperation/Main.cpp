#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <chrono>

#include "Bank.h"

int main(void)
{
	system("chcp 1251 && cls");
	Bank t;
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
		std::cout << " 0. Открыть новый счет.\n";
		std::cout << " 1. Показать текущее состояние счета.\n";
		std::cout << " 2. Закрыть счет.\n";
		std::cout << " 3. Изменить состояние счета\n";
		std::cout << " 4. Показать информацию по всем счетам.\n";
		std::cout << " 5. Очистка консоли\n";
		std::cout << "Иначе Выход\n";
		char ch = std::cin.get();
		std::cin.ignore(255, '\n');
		switch (ch)
		{
		case '0':
		{
			t.OpenAccount();
			break;
		}
		case '1':
		{
			t.ShowInfo();
			break;
		}
		case '2':
		{
			t.CloseAccount();
			break;
		}
		case '3':
		{
			t.EditAccount();
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

