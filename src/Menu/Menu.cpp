#include "Menu.h"

Menu::Menu(const int& size)
{
	this->size = size;
	this->count = 0;
	this->current = -1;
	this->numbers = new RationalNumbers[this->size];
}

Menu::Menu(const RationalNumbers* arr, int size)
{
	this->size = size;
	this->numbers = new RationalNumbers[this->size];
	for (size_t i = 0; i < this->size; ++i)
		this->numbers[i] = arr[i];
	this->count = this->size;
}

Menu::~Menu()
{
	delete[] this->numbers;
	this->numbers = nullptr;
	this->size = 0;
	this->count = 0;
}

void Menu::run()
{
	std::cout << "Hello, this program allows you to work winth the RationalNumbers library.\n";
	std::cout << "Use the menu to work with class obbject.\n";
	std::cout << "(object indexing starts from 0)\n";
	bool stop = false;
	do 
	{
		std::cout << "\nMenu items:\n";
		std::cout << "1. Create an object of the class.\n";
		std::cout << "2. Save/load object to disk.\n";
		std::cout << "3. Print object.\n";
		std::cout << "4. Perform operations on object.\n";
		std::cout << "0. Exit.\n";

		int choise = 0;
		input(choise);
		switch (choise)
		{
		case 1:
			this->createObj();
			break;
		case 2:
			this->objDisk();
			break;
		case 3:
			this->print();
			break;
		case 4:
			this->operation();
			break;
		case 0:
			stop = true;
			break;
		default:
			std::cout << "Incorrect input.\n";
			break;
		}
	} while (!stop);
}

void Menu::input(int& input)
{
	std::cout << "> ";
	std::cin >> input;
	std::cin.ignore(32767, '\n');
}

void Menu::input(char* input)
{
	std::cout << "> ";
	std::cin.getline(input, 32);
}

void Menu::input(char& input)
{
	std::cout << "> ";
	std::cin >> input;
	std::cin.ignore(32767, '\n');
}

void Menu::add(RationalNumbers number)
{
	if (this->count == this->size)
	{
		RationalNumbers* newNumbers = new RationalNumbers[this->size * 2];
		for (size_t i = 0; i < this->size; ++i)
			newNumbers[i] = this->numbers[i];
		delete[] this->numbers;
		this->numbers = newNumbers;
		this->size *= 2;
	}
	this->numbers[this->count] = number;
	this->count++;
}

void Menu::save()
{
	int currentObj = NULL;
	do
	{
		std::cout << "Select the current object index.\n";
		input(currentObj);
	} while (!setCurrent(currentObj));

	std::cout << "Enter the file path.\n";
	char filePath[32];
	input(filePath);

	this->save(filePath);
}

void Menu::loadToList(const RationalNumbers& numberToLoad) {
	std::cout << "Choose an action:\n";
	std::cout << "1. Add object.\n";
	std::cout << "2. Replace the object.\n";

	bool stop = true;
	do
	{
		int action = NULL;
		input(action);
		switch (action)
		{
		case 1:
		{
			this->add(numberToLoad);
		}
		break;
		case 2:
		{
			int currentObj = NULL;
			do
			{
				std::cout << "Select the current object index.\n";
				input(currentObj);
			} while (!setCurrent(currentObj));

			this->numbers[currentObj] = numberToLoad;
		}
		break;
		default:
			std::cout << "Incorrect input.\n";
			stop = false;
			break;
		}
	} while (!stop);
}

void Menu::loadFromFile()
{
	std::cout << "Enter the file path.\n";
	char filePath[32];
	input(filePath);

	while (!check(filePath))
	{
		std::cout << "Invalid file path.\n";
		input(filePath);
	}

	RationalNumbers temp;
	temp.load(filePath);

	loadToList(temp);
}

void Menu::print()
{
	for (size_t i = 0; i < this->count; ++i) {
		std::cout << "Element #" << i << " = " << this->numbers[i] << "\n";
	}
}

void Menu::save(const char* outputFilePath)
{
	this->numbers[this->current].save(outputFilePath);
}

bool Menu::load(const char* inputFilePath)
{
	return this->numbers[this->current].load(inputFilePath);
}

bool Menu::setCurrent(int choise)
{
	if (this->count > choise)
	{
		this->current = choise;
		return true;
	}
	else return false;
}

void Menu::createObj()
{
	std::cout << "Enter the object data:\n";
	RationalNumbers addNumber;
	std::cin >> addNumber;
	this->add(addNumber);
}

void Menu::objDisk()
{
	bool stop = true;
	do
	{
		std::cout << "Choose an action:\n";
		std::cout << "1. Save.\n";
		std::cout << "2. Load.\n";
		std::cout << "0. Exit.\n";

		int choice = NULL;
		input(choice);

		switch (choice)
		{
		case 1:
			this->save();
			break;
		case 2:
		{
			this->loadFromFile();
		}
		break;
		case 0:
			break;
		default:
		{
			std::cout << "Incorrect input.\n";
			stop = false;
		}
		break;
		}
	} while (!stop);
}

void Menu::mathOperation()
{
	std::cout << "Select start element index:\n";
	int choiceElement;
	input(choiceElement);
	this->setCurrent(choiceElement);
	std::cout << "Select operation:\n";
	std::cout << "1. +\n2. -\n3. *\n4. /\n5. ^\n";
	int choiceOperation;
	input(choiceOperation);
	while (choiceOperation > 5 || choiceOperation < 1) {
		std::cout << "Incorrect choice.\n";
		input(choiceOperation);
	}
	RationalNumbers result(this->numbers[this->current]);
	if (choiceOperation != 5)
	{
		std::cout << "Select second element index:\n";
		input(choiceElement);
		this->setCurrent(choiceElement);
	}
	else
	{
		std::cout << "Select power index:\n";
		input(choiceElement);
	}
	switch (choiceOperation)
	{
	case 1:
		result += this->numbers[this->current];
		break;
	case 2:
		result -= this->numbers[this->current];
		break;
	case 3:
		result *= this->numbers[this->current];
		break;
	case 4:
		result = result / this->numbers[this->current];
		break;
	case 5:
		result ^= choiceElement;
		break;
	default:
		std::cout << "Error\n";
		break;
	}

	std::cout << "Result: " << result << "\n";
	std::cout << "Do you want to save the result?\n";
	std::cout << "1. Save\n0. Exit\n";
	int choiceSave = NULL;
	
	bool stop = NULL;
	do {
		input(choiceSave);
		switch (choiceSave)
		{
		case 1:
			this->loadToList(result);
			stop = true;
			break;
		case 0:
			stop = true;
			break;
		default:
			std::cout << "Invalid choice\n";
			stop = false;
			break;
		}
	} while (!stop);
}

void Menu::typeCastingOperation() {
	std::cout << "Select element index:\n";
	int choiseElement;
	input(choiseElement);
	this->setCurrent(choiseElement);
	std::cout << "Select the drive type:\n";
	std::cout << "1. int\n2. double\n3. float\n";
	int choiseOperation;
	bool stop = NULL;
	do {
		input(choiseOperation);
		stop = false;
		switch (choiseOperation)
		{
		case 1:
			std::cout << "Result: " << (int)this->numbers[this->current];
			break;
		case 2:
			std::cout << "Result: " << (double)this->numbers[this->current];
			break;
		case 3:
			std::cout << "Result: " << (float)this->numbers[this->current];
			break;
		default:
			std::cout << "Invalid choice\n";
			stop = true;
			break;
		}
	} while (stop);
}

void Menu::changeValObj() {
	std::cout << "Select element index:\n";
	int choiseElement;
	input(choiseElement);
	this->setCurrent(choiseElement);
	int numerator = NULL;
	std::cout << "Numerator:\n";
	input(numerator);
	this->numbers[this->current](0) = numerator;
	int denominator = NULL;
	std::cout << "Denominator:\n";
	input(denominator);
	this->numbers[this->current](1) = denominator;
}

void Menu::operation() {
	std::cout << "Select the type of operations you want to perform:\n";
	std::cout << "1. Mathematical operation.\n";
	std::cout << "2. Type casting operations.\n";
	std::cout << "3. Replace value object.\n";
	int choiseOperation;
	bool stop = NULL;
	do {
		input(choiseOperation);
		stop = false;
		switch (choiseOperation)
		{
		case 1:
			this->mathOperation();
			break;
		case 2:
			this->typeCastingOperation();
			break;
		case 3:
			this->changeValObj();
			break;
		default:
			std::cout << "Invalid choice\n";
			stop = true;
			break;
		}
	} while (stop);
}