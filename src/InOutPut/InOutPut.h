#ifndef _INOUTPUT_H
#define _INOUTPUT_H

#include <fstream>

class InOutPut
{
public:
	virtual void save(const char* outputFilePath) = 0;
	virtual bool load(const char* inputFilePath) = 0;
protected:
	bool check(const char* inputFilePath);
};

#endif // _INOUTPUT_H