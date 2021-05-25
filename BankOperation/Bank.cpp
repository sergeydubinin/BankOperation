#define _CRT_SECURE_NO_WARNINGS
#include "Bank.h"
#include <iostream>
#include <sstream>

std::tm get_current_date()
{
	//текущее время
	auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::tm now_tm = *std::localtime(&now);
	return now_tm;
}

void Bank::OpenAccount()
{
	int code;
	std::cout << "Введите 1 для обычного вклада\t2 для срочного\tиначе - валютного\n";
	std::cin >> code;
	if (code == 1)
	{
		unsigned long id;
		CurrencyType sum;
		std::tm date{};
		std::string d;
		double percent;
		std::cout << "Введите id:";
		std::cin >> id;
		std::cout << "Введите сумму вклада:";
		std::cin >> sum;
		std::cout << "Введите процент ежемесячного пополнения:";
		std::cin >> percent;
		std::cout << "Введите дату открытия в формате yyyy-mm-dd:";
		std::cin >> d;
		std::istringstream ss(d);
		ss >> std::get_time(&date, "%Y-%m-%d");
		if (ss.fail())
		{
			return;
		}
		m_data.Add(new UsualDeposit(id, sum, date, percent));
		std::cout << "Запись добавлена\n";
		std::cin.get();
	}
	else if (code == 2)
	{
		unsigned long id;
		CurrencyType sum;
		std::tm date{}, expDate{};
		std::string d;
		double percent;
		std::cout << "Введите id:";
		std::cin >> id;
		std::cout << "Введите сумму вклада:";
		std::cin >> sum;
		std::cout << "Введите процент ежемесячного пополнения:";
		std::cin >> percent;
		std::cout << "Введите дату открытия в формате yyyy-mm-dd:";
		std::cin >> d;
		std::istringstream ss(d);
		ss >> std::get_time(&date, "%Y-%m-%d");
		if (ss.fail())
		{
			return;
		}
		ss.clear();
		std::cout << "Введите дату истечения в формате yyyy-mm-dd:";
		std::cin >> d;
		ss.str(d);
		ss >> std::get_time(&expDate, "%Y-%m-%d");
		if (ss.fail())
		{
			return;
		}
		m_data.Add(new TermDeposit(id, sum, date, percent, expDate));
		std::cout << "Запись добавлена\n";
		std::cin.get();
	}
	else
	{
		unsigned long id;
		CurrencyType sum;
		std::tm date{};
		std::string d, c;
		double percent, rate;
		std::cout << "Введите id:";
		std::cin >> id;
		std::cout << "Введите сумму вклада:";
		std::cin >> sum;
		std::cout << "Введите процент ежемесячного пополнения:";
		std::cin >> percent;
		std::cout << "Введите дату открытия в формате yyyy-mm-dd:";
		std::cin >> d;
		std::istringstream ss(d);
		ss >> std::get_time(&date, "%Y-%m-%d");
		if (ss.fail())
		{
			return;
		}
		ss.clear();
		std::cout << "Введите валюту:";
		std::cin >> c;
		std::cout << "Введите курс:";
		std::cin >> rate;
		m_data.Add(new CurrencyDeposit(id, sum, date, percent, c, rate));
		std::cout << "Запись добавлена\n";
		std::cin.get();
	}
}

void Bank::ShowInfo()
{
	unsigned long id;
	std::cout << "Введите id:";
	std::cin >> id;
	auto dep = m_data.getByID(id);
	if (dep != nullptr)
	{
		std::cout << "На счету:" << dep->getSum() << '\n';
		std::cout << "Процентов начислено:" << dep->calculateProfit(get_current_date()) << '\n';
	}
	else
	{
		std::cout << "Счет с id = " << id << " не найден\n";
	}
	std::cin.get();
}

void Bank::CloseAccount()
{
	unsigned long id;
	std::cout << "Введите id:";
	std::cin >> id;
	auto dep = m_data.getByID(id);
	if (dep != nullptr)
	{
		std::cout << "Возвращено:" << dep->getSum() + dep->calculateProfit(get_current_date()) << '\n';
		m_data.removeByID(id);
	}
	else
	{
		std::cout << "Счет с id = " << id << " не найден\n";
	}
	std::cin.get();

}

void Bank::EditAccount()
{
	unsigned long id;
	std::cout << "Введите id:";
	std::cin >> id;
	auto dep = m_data.getByID(id);
	if (dep == nullptr)
	{
		std::cout << "Счет с id = " << id << " не найден\n";
		return;
	}

	//если вклад срочный, то его нельзя модифицировать
	auto ptr = dynamic_cast<TermDeposit*>(dep);
	if (ptr != nullptr)
	{
		std::cout << "Вы не можете редактировать срочный вклад\n";
		return;
	}

	int code;
	std::tm date{};
	std::string d;
	CurrencyType sum;
	std::cout << "Введите 1 для пополнения вклада\t2 для снятия\tиначе - снятие процентов\n";
	std::cin >> code;
	if (code == 1)
	{
		std::cout << "Введите дату поплнения в формате yyyy-mm-dd:";
		std::cin >> d;
		std::istringstream ss(d);
		ss >> std::get_time(&date, "%Y-%m-%d");
		if (ss.fail())
		{
			return;
		}
		ss.clear();
		std::cout << "Введите сумму:";
		std::cin >> sum;
		dep->updateSum(sum, date);
		std::cout << "Баланс обновлен\n";
	}
	else if (code == 2)
	{
		std::cout << "Введите дату снятия в формате yyyy-mm-dd:";
		std::cin >> d;
		std::istringstream ss(d);
		ss >> std::get_time(&date, "%Y-%m-%d");
		if (ss.fail())
		{
			return;
		}
		ss.clear();
		std::cout << "Введите сумму:";
		std::cin >> sum;
		dep->updateSum(-sum, date);
		std::cout << "Баланс обновлен\n";
	}
	else
	{
		auto date = get_current_date();
		std::cout << "Накопления: " << dep->calculateProfit(date) << " выплачены\n";
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