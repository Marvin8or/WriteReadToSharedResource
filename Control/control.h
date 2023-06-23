#pragma once
#include <vector>
#include <mutex>
#include <condition_variable>
#include "../Utils/utils.h"
using namespace std;

class ControlAPI
{
private:
	int maxBufferSize;
	const int maxOperationsNum = 100;
	std::mutex controlMutex;
	int currentWriteIndex = 0;
	int currentReadIndex = 0;
	vector<Data*>* sharedResourcePtr;
	std::condition_variable bufferIsFull;
	std::condition_variable bufferIsEmpty;

public:
	ControlAPI(int size);
	void write(int threadNum);
	void read(int threadNum);
	void initialize();
	int getWriteIndex() { return this->currentWriteIndex; }
	int getReadIndex() { return this->currentReadIndex; }
	vector<Data*>* getSharedResourcePtr() { return this->sharedResourcePtr; }
};
