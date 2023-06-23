#pragma once

#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include "utils.h"

using namespace std;

/*
 * Prints the contents of a buffer.
 * @param size The size of the buffer.
 * @param data Pointer to the vector of Data pointers representing the buffer.
 */
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


/*
 * Genrate a random integer nuber using mt19937 algorithm in a uniform distribution
 * @param min_val The minimum value of the range.
 * @param max_val The maximum value of the range.
 * @return A random number within the specified range.
 */
int generateRandomNumber(int min_val, int max_val)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(min_val, max_val);
	return dist(gen);
}

/*
 * Function that makes thread sleep for a given number of milliseconds.
 * @param threadNum The thread number indicating the calling thread.
 * @param value Milliseconds to make thread sleep
 */
void sleepFor(int threadNum, int value)
{
	cout << "Thread[" << threadNum << "] sleeping for " << value << "ms ... " << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(value));
}
