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
		this->controlMutex.lock();
		//int valueToWrite = generateRandomNumber(1, 10); //ToDo create on heap
		int nextWriteIndex = (this->currentWriteIndex + 1) % maxBufferSize;
		if (nextWriteIndex == this->currentReadIndex)
		{
			// Wait till consumer catches up
			cout << "Thread[" << threadNum << "] Waiting for reader..." << endl;
			this->controlMutex.unlock();
			sleepFor(threadNum, 100);
		}
		else
		{
			Data* dataToWrite = new Data;
			dataToWrite->dataInt1 = generateRandomNumber(1, 10);
			dataToWrite->dataInt2 = generateRandomNumber(1, 10);
			cout << "Thread[" << threadNum << "] Writing at index [" << this->currentWriteIndex << "]: " << dataToWrite->dataInt1 << endl;

			this->sharedResourcePtr->at(this->currentWriteIndex) = dataToWrite;
			this->currentWriteIndex = nextWriteIndex;
			this->controlMutex.unlock();
			sleepFor(threadNum, 100);
		}
	}

}

void ControlAPI::read(int threadNum)
{
	int readOperationCounter = 0;
	while (readOperationCounter++ != this->maxOperationsNum)
	{
		this->controlMutex.lock();
		int nextReadIndex = (this->currentReadIndex + 1) % maxBufferSize;

		if (this->currentReadIndex == this->currentWriteIndex)
		{
			// Wait for reader to catch up with writer
			cout << "Thread[" << threadNum << "] Waiting for writer..." << endl;
			this->controlMutex.unlock();
			sleepFor(threadNum, 100);
		}
		else
		{
			Data* consumedValue = this->sharedResourcePtr->at(this->currentReadIndex);
			cout << "Thread[" << threadNum << "] Reading at index [" << this->currentReadIndex << "]: " << consumedValue->dataInt1 << endl;
			delete consumedValue;

			this->currentReadIndex = nextReadIndex;
			this->controlMutex.unlock();
			sleepFor(threadNum, 100);
		}


	}
}

void printBuffer(int size, vector<Data*>* data)
{
	cout << "[";
	for (int i = 0; i < size; i++)
	{
		if (i == size - 1)
		{
			cout << "{ data1: " << data->at(i)->dataInt1 << ", data2: " << data->at(i)->dataInt2 << "}";
		}
		else
		{
			cout << "{ data1: " << data->at(i)->dataInt1 << ", data2: " << data->at(i)->dataInt2 << "}, ";
		}
	}
	cout << "]" << endl;
}



// For now acts as initialize variable
int generateRandomNumber(int min_val, int max_val)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(min_val, max_val);
	return dist(gen);
}


void sleepFor(int threadNum, int value)
{
	cout << "Thread[" << threadNum << "] sleeping for " << value << "ms ... " << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(value));
}
