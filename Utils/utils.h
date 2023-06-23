#pragma once
#include <vector>
using namespace std;

struct Data
{
	int dataInt1;
	int dataInt2;
};


int generateRandomNumber(int min_val, int max_val);
void sleepFor(int threadNum, int value);
void printBuffer(int maxBufferSize, vector<Data*>* data);