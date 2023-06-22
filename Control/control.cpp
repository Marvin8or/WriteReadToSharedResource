#include <iostream>
#include <random>
#include <chrono>
#include "control.h"
using namespace std;

void write(int threadNum, std::mutex& m, vector<int>* sharedResource, int& counter)
{
	int writeOperationCounter = 0;
	while(writeOperationCounter++ != maxOperations)
	{
		m.lock();
		if (counter < maxBufferSize)
		{
			int valueToWrite = generateRandomNumber(1, 10); //ToDo create on heap
			cout << "Thread[" << threadNum << "] Writing: " << valueToWrite << endl;
			sharedResource->push_back(valueToWrite);
			counter++;
		}
		else
		{
			cout << "Thread[" << threadNum << "] skipped"<< endl;

		}
		m.unlock();
		cout << "Thread[" << threadNum << "] ";
		sleepFor(100);
	}
}	

void read(int threadNum, std::mutex& m, vector<int>* sharedResource, int& counter)
{
	int readOperationCounter = 0;
	while(readOperationCounter++ != maxOperations)
	{
		int consumedValue = -1;
		m.lock();
		if(counter > 0)
		{
			consumedValue = sharedResource->back();
			sharedResource->pop_back();
			counter--;
			cout << "Thread[" << threadNum << "] Got: " << consumedValue << endl;
			m.unlock();
			
		}
		else
		{
			m.unlock();
			cout << "Thread[" << threadNum << "] ";
			sleepFor(500);
		}
		
		
	}
}

vector<int>* initialize()
{
	vector<int>* shared_resource = new vector<int>;
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

void sleepFor(int value)
{
	cout << "Sleeping for " << value << "ms ... " << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(value));
}

//ToDo For now takes int array
void printBuffer(vector<int>* resource, int* count)
{
	cout << "[";
	for (int i = 0; i < *count; i++)
	{
		if(i == (*count) - 1)
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