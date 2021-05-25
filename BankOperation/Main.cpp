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
		std::cout << " 0. ������� ����� ����.\n";
		std::cout << " 1. �������� ������� ��������� �����.\n";
		std::cout << " 2. ������� ����.\n";
		std::cout << " 3. �������� ��������� �����\n";
		std::cout << " 4. �������� ���������� �� ���� ������.\n";
		std::cout << " 5. ������� �������\n";
		std::cout << "����� �����\n";
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

