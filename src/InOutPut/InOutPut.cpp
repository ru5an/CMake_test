#include "InOutPut.h"

bool InOutPut::check(const char* inputFilePath) {
	std::ifstream inputFile(inputFilePath);
	return inputFile.good();
}