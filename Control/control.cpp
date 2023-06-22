#include <iostream>
#include <random>
#include <chrono>
#include "control.h"
using namespace std;

void write(int threadNum, std::mutex& m, vector<int>* sharedResource, int& readIndex, int& writeIndex)
{
	int writeOperationCounter = 0;
	while(writeOperationCounter++ != maxOperations)
	{
		m.lock();
		int valueToWrite = generateRandomNumber(1, 10); //ToDo create on heap
		int nextWriteIndex = (writeIndex + 1) % maxBufferSize;
		if(nextWriteIndex == readIndex)
		{
			// Wait till consumer cathes up
			cout << "Thread[" << threadNum << "] Waiting for reader..." << endl;
			m.unlock();
			sleepFor(threadNum, 100);
		}
		else
		{
			cout << "Thread[" << threadNum << "] Writing at index ["<< writeIndex << "]: " << valueToWrite << endl;
			sharedResource->at(writeIndex) = valueToWrite;
			writeIndex = nextWriteIndex;
			m.unlock();
			sleepFor(threadNum, 100);
		}
	}
}	

void read(int threadNum, std::mutex& m, vector<int>* sharedResource, int& readIndex, int& writeIndex)
{
	int readOperationCounter = 0;
	while(readOperationCounter++ != maxOperations)
	{
		m.lock();
		int nextReadIndex = (readIndex + 1) % maxBufferSize;

		if(readIndex == writeIndex)
		{
			// Wait for reader to catch up with writer
			cout << "Thread[" << threadNum << "] Waiting for writer..." << endl;
			m.unlock();
			sleepFor(threadNum, 100);
		}
		else
		{
			int consumedValue = sharedResource->at(readIndex);
			cout << "Thread[" << threadNum << "] Got at index [" << readIndex << "]: " << consumedValue << endl;
			readIndex = nextReadIndex;
			m.unlock();
			sleepFor(threadNum, 100);
		}

		
	}
}

vector<int>* initialize()
{
	vector<int>* shared_resource = new vector<int>(maxBufferSize);
	return shared_resource;
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

//ToDo For now takes int array
void printBuffer(vector<int>* resource)
{
	cout << "[";
	for (int i = 0; i < maxBufferSize; i++)
	{
		if(i == maxBufferSize - 1)
		{
			cout << resource->at(i);
		}
		else
		{
			cout << resource->at(i) << ", ";
		}
	}
	cout << "]" << endl;
}