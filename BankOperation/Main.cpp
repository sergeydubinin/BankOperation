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
	t.LoadFromFile("file.txt");

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
			t.SaveToFile("file.txt");
			return 0;
		}
		}
	} while (true);
}

