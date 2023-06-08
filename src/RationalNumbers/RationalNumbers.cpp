#include "RationalNumbers.h"

RationalNumbers::RationalNumbers(const int& numerator, const int& denominator) {
	m_Numerator = new int(numerator);
	m_Denominator = new int(denominator);
	this->IrreducibleFraction();
}

RationalNumbers::~RationalNumbers() {
	delete m_Numerator;
	delete m_Denominator;
}

RationalNumbers::RationalNumbers(const RationalNumbers& rational_number) {
	this->m_Numerator = new int(*(rational_number.m_Numerator));
	this->m_Denominator = new int(*(rational_number.m_Denominator));
	this->IrreducibleFraction();
}

int& RationalNumbers::operator()(const int& index) {
	if (index == 0) {
		return *m_Numerator;
	}
	else if (index == 1) {
		return *m_Denominator;
	}
	else {
		std::cerr << "Invalid index\n";
		exit(EXIT_FAILURE);
	}
}

int RationalNumbers::operator[](const int& index) {
	if (index == 0) {
		return *m_Numerator;
	}
	else if (index == 1) {
		return *m_Denominator;
	}
	else {
		std::cerr << "Invalid index\n";
		exit(EXIT_FAILURE);
	}
}

RationalNumbers* RationalNumbers::operator->() { return this; }

RationalNumbers::operator int() const { return *m_Numerator / *m_Denominator; }

RationalNumbers::operator double() const { return (double)*m_Numerator / (double)*m_Denominator; }

RationalNumbers::operator float() const { return (float)*m_Numerator / (float)*m_Denominator; }

std::ostream& operator<<(std::ostream& os, const RationalNumbers& rational_number) {
	os << "( " << *(rational_number.m_Numerator) << " / " << *(rational_number.m_Denominator) << " )";
	return os;
}

std::istream& operator>>(std::istream& is, RationalNumbers& rational_number) {
	int numerator, denominator;
	std::cout << "Numerator\n> ";
	is >> numerator;
	std::cout << "Denominator\n> ";
	is >> denominator;
	rational_number = RationalNumbers(numerator, denominator);
	return is;
}

int GCT(const int& numerator, const int& denominator) {
	if (denominator == 0)
		return numerator;
	return GCT(denominator, numerator % denominator);
}

int LCM(const int& numerator, const int& denominator) {
	return (numerator * denominator) / GCT(numerator, denominator);
}

RationalNumbers& RationalNumbers::IrreducibleFraction() {
	int* divisor = new int(GCT(*(m_Numerator), *(m_Denominator)));
	if (*divisor != 1) {
		*m_Numerator = *(m_Numerator) / *divisor;
		*m_Denominator = *(m_Denominator) / *divisor;
	}
	delete divisor;
	divisor = nullptr;
	return *this;
}

RationalNumbers operator+(const RationalNumbers& left, const RationalNumbers& right) {
	int lcm = LCM(*(left.m_Denominator), *(right.m_Denominator));
	int numerator = (*left.m_Numerator) * (lcm / (*left.m_Denominator)) + (*(right.m_Numerator)) * (lcm / (*(right.m_Denominator)));
	RationalNumbers sum(numerator, lcm);
	sum.IrreducibleFraction();
	return sum;
}

RationalNumbers operator-(const RationalNumbers& left, const RationalNumbers& right) {
	int lcm = LCM(*(left.m_Denominator), *(right.m_Denominator));
	int numerator = (*left.m_Numerator) * (lcm / (*left.m_Denominator)) - (*(right.m_Numerator)) * (lcm / (*(right.m_Denominator)));
	RationalNumbers difference(numerator, lcm);
	difference.IrreducibleFraction();
	return difference;
}

RationalNumbers operator*(const RationalNumbers& left, const RationalNumbers& right) {
	int numerator = *(left.m_Numerator) * *(right.m_Numerator);
	int denominator = *(left.m_Denominator) * *(right.m_Denominator);
	RationalNumbers product(numerator, denominator);
	product.IrreducibleFraction();
	return product;
}

RationalNumbers operator/(const RationalNumbers& left, const RationalNumbers& right) {
	int numerator = *(left.m_Numerator) * *(right.m_Denominator);
	int denominator = *(left.m_Denominator) * *(right.m_Numerator);
	RationalNumbers divison(numerator, denominator);
	divison.IrreducibleFraction();
	return divison;
}

RationalNumbers operator^(const RationalNumbers& left, const int& index) {

	int numerator = pow(*(left.m_Numerator), index);
	int denominator = pow(*(left.m_Denominator), index);
	RationalNumbers power(numerator, denominator);
	power.IrreducibleFraction();
	return power;
}

RationalNumbers& RationalNumbers::operator=(const RationalNumbers& rational_number) {
	if (this != &rational_number) {
		delete m_Numerator;
		delete m_Denominator;
		m_Numerator = new int(*(rational_number.m_Numerator));
		m_Denominator = new int(*(rational_number.m_Denominator));
		this->IrreducibleFraction();
	}
	return *this;
}

RationalNumbers& RationalNumbers::operator+=(const RationalNumbers& rational_number) {
	*this = *this + rational_number;
	this->IrreducibleFraction();
	return *this;
}

RationalNumbers& RationalNumbers::operator-=(const RationalNumbers& rational_number) {
	*this = *this - rational_number;
	this->IrreducibleFraction();
	return *this;
}

RationalNumbers& RationalNumbers::operator*=(const RationalNumbers& rational_number) {
	*this = *this * rational_number;
	this->IrreducibleFraction();
	return *this;
}

RationalNumbers& RationalNumbers::operator/=(const RationalNumbers& rational_number) {
	*this = *this / rational_number;
	this->IrreducibleFraction();
	return *this;
}

RationalNumbers& RationalNumbers::operator^=(const int& index) {
	*this = *this ^ index;
	this->IrreducibleFraction();
	return *this;
}

void RationalNumbers::save(const char* outputFilePath) {
	std::ofstream outputFile(outputFilePath);
	outputFile << *this;
}

bool RationalNumbers::load(const char* inputFilePath) {
	if (!check(inputFilePath)) return false;
	std::ifstream inputFile(inputFilePath);
	char inputLine[32];
	inputFile.getline(inputLine, 32);
	sscanf_s(inputLine, "( %d / %d )", this->m_Numerator, this->m_Denominator);
	return true;
}