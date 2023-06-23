#include <iostream>
#include <random>
#include <chrono>
#include "control.h"

using namespace std;

ControlAPI::ControlAPI(int size)
{
	if(size <= 0)
	{
		std::cerr << "Size must be greater than 0!" << std::endl;
	}

	this->maxBufferSize = size;
}

void ControlAPI::initialize()
{
	this->sharedResourcePtr = new vector<Data*>(this->maxBufferSize);
	if(this->sharedResourcePtr == nullptr)
	{
		std::cerr << "Unable to allocate shared resource!";
	}
}

void ControlAPI::write(int threadNum)
{
	int writeOperationCounter = 0;
	while (writeOperationCounter++ != this->maxOperationsNum)
	{
		std::unique_lock<std::mutex> lock(this->controlMutex);

		int nextWriteIndex = (this->currentWriteIndex + 1) % maxBufferSize;

		this->bufferIsFull.wait(lock,[nextWriteIndex, this] {return nextWriteIndex != this->currentReadIndex; });

		Data* dataToWrite = new Data;
		dataToWrite->dataInt1 = generateRandomNumber(1, 10);
		dataToWrite->dataInt2 = generateRandomNumber(1, 10);
		cout << "Thread[" << threadNum << "] Writing at index [" << this->currentWriteIndex << "]: " << dataToWrite->dataInt1 << endl;

		this->sharedResourcePtr->at(this->currentWriteIndex) = dataToWrite;
		this->currentWriteIndex = nextWriteIndex;
		lock.unlock();

		this->bufferIsEmpty.notify_one();
		
	}
}

void ControlAPI::read(int threadNum)
{
	int readOperationCounter = 0;
	while (readOperationCounter++ != this->maxOperationsNum)
	{
		// Added sleep to simulate faster writing than reading
		sleepFor(threadNum, 100);

		std::unique_lock<std::mutex> lock(this->controlMutex);

		int nextReadIndex = (this->currentReadIndex + 1) % maxBufferSize;

		this->bufferIsEmpty.wait(lock, [this] {return this->currentReadIndex != this->currentWriteIndex; });
		Data* consumedValue = this->sharedResourcePtr->at(this->currentReadIndex);
		cout << "Thread[" << threadNum << "] Reading at index [" << this->currentReadIndex << "]: " << consumedValue->dataInt1 << endl;
		delete consumedValue;

		this->currentReadIndex = nextReadIndex;
		lock.unlock();
		this->bufferIsFull.notify_one();
	}
}
