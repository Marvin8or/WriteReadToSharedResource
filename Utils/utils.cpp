#pragma once

#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include "utils.h"

using namespace std;
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
