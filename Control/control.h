#pragma once
#include <iostream>
#include <vector>
#include <mutex>
using namespace std;


struct Data
{
	int dataInt1;
	int dataInt2;
};


class ControlAPI
{
private:
	int maxBufferSize;
	const int maxOperationsNum = 100;
	std::mutex controlMutex;
	int currentWriteIndex = 0;
	int currentReadIndex = 0;
	vector<Data*>* sharedResourcePtr;

public:
	ControlAPI(int size);
	void write(int threadNum);
	void read(int threadNum);
	void initialize();
	int getWriteIndex() { return this->currentWriteIndex; }
	int getReadIndex() { return this->currentReadIndex; }
	vector<Data*>* getSharedResourcePtr() { return this->sharedResourcePtr; }
};

int generateRandomNumber(int min_val, int max_val); //ToDo GOES INTO HELPER/UTILS
void sleepFor(int threadNum, int value); //ToDo GOES INTO HELPER/UTILS
void printBuffer(int maxBufferSize, vector<Data*>* data);