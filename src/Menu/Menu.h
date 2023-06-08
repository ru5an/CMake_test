#ifndef _MENU_H_
#define _MENU_H_

#include "..\RationalNumbers\RationalNumbers.h"

class Menu : public InOutPut
{
public:
	Menu(const int& size = 1);
	Menu(const RationalNumbers* arr, int size);
	~Menu();

	void run();
protected:
	void input(int& input);
	void input(char* input);
	void input(char& input);

	void add(RationalNumbers number);
	void save();
	void loadFromFile();
	void loadToList(const RationalNumbers& numberToLoad);
	virtual void save(const char* outputFilePath);
	virtual bool load(const char* inputFilePath);
	bool setCurrent(int choise);

	void createObj();
	void objDisk();
	void print();

	void operation();
	void mathOperation();
	void typeCastingOperation();
	void changeValObj();
private:
	RationalNumbers* numbers;
	int count;
	int size;
	int current;
};

#endif // !_MENU_H_