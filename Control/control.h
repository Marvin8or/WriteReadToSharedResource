#pragma once
#include <vector>
#include <mutex>
#include <condition_variable>
#include "../Utils/utils.h"
using namespace std;

class ControlAPI
{
private:

	// Maximum length of the buffer of the shared resource
	int maxBufferSize;

	// Maximum number of operations read/write
	const int maxOperationsNum = 1000;

	// Mutex object to control locking and unlocking
	std::mutex controlMutex;

	// Current writing index in shared resource
	int currentWriteIndex = 0;

	// Current reading index in shared resource
	int currentReadIndex = 0;

	// Pointer to shared resource: vector of pointers to Data stucts, allocated on heap and deallocated after reading
	vector<Data*>* sharedResourcePtr;

	// Condition variable for when the buffer is full
	std::condition_variable bufferIsFull;

	// Condition variable for when the buffer is empty
	std::condition_variable bufferIsEmpty;

public:
	// C'tor
	ControlAPI(int size);

	void write(int threadNum);
	void read(int threadNum);
	void initialize();
	int getWriteIndex() { return this->currentWriteIndex; }
	int getReadIndex() { return this->currentReadIndex; }
	vector<Data*>* getSharedResourcePtr() { return this->sharedResourcePtr; }
};
