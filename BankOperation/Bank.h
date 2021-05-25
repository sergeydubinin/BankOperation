#include "Table.h"

class Bank
{
public:
	void OpenAccount();
	void ShowInfo();
	void CloseAccount();
	void EditAccount();
	void LoadFromFile(const std::string& fileName);
	void SaveToFile(const std::string& fileName);

	bool Add(Deposit* ptr) { return m_data.Add(ptr); };
	void print() const { m_data.print(); };
private:
	Table m_data;
};
