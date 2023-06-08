#ifndef _RATIONALNUMBERS_H_
#define _RATIONALNUMBERS_H_

#include <iostream>
#include "..\InOutPut\InOutPut.h"

class RationalNumbers : public InOutPut
{
	friend std::ostream& operator<<(std::ostream& os, const RationalNumbers& rational_number);
	friend std::istream& operator>>(std::istream& is, RationalNumbers& rational_number);

	friend RationalNumbers operator+(const RationalNumbers& left, const RationalNumbers& right);
	friend RationalNumbers operator-(const RationalNumbers& left, const RationalNumbers& right);
	friend RationalNumbers operator*(const RationalNumbers& left, const RationalNumbers& right);
	friend RationalNumbers operator/(const RationalNumbers& left, const RationalNumbers& right);
	friend RationalNumbers operator^(const RationalNumbers& left, const int& index);
public:
	RationalNumbers(const int& numerator = 0, const int& denominator = 1);
	~RationalNumbers();
	RationalNumbers(const RationalNumbers& rational_number);

	int& operator()(const int& index);
	int operator[](const int& index);
	RationalNumbers* operator->();

	operator int() const;
	operator double() const;
	operator float() const;

	RationalNumbers& operator=(const RationalNumbers& rational_number);
	RationalNumbers& operator+=(const RationalNumbers& rational_number);
	RationalNumbers& operator-=(const RationalNumbers& rational_number);
	RationalNumbers& operator*=(const RationalNumbers& rational_number);
	RationalNumbers& operator/=(const RationalNumbers& rational_number);
	RationalNumbers& operator^=(const int& index);

	virtual void save(const char* outputFilePath);
	virtual bool load(const char* inputFilePath);
protected:
	RationalNumbers& IrreducibleFraction();
private:
	int* m_Numerator;
	int* m_Denominator;
};

#endif // !_RATIONALNUMBERS_H_