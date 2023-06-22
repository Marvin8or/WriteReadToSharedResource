#pragma once
#include <vector>
using namespace std;

struct Data
{
	int dataInt1;
	int dataInt2;
};


int generateRandomNumber(int min_val, int max_val); //ToDo GOES INTO HELPER/UTILS
void sleepFor(int threadNum, int value); //ToDo GOES INTO HELPER/UTILS
void printBuffer(int maxBufferSize, vector<Data*>* data);