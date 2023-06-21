#include <iostream>
#include <mutex>
#include <random>
#include <chrono>
#include "control.h"
using namespace std;

void write(int value)
{
	cout << " Write to buffer: " << value << endl;
}

void read()
{
	cout << "Read from buffer" << endl;
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

void sleepFor(int seconds)
{
	cout << "Sleeping for " << seconds << "s ... " << endl;
	std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

//ToDo For now takes vector<int>
void printBuffer(vector<int>* resource) 
{
	cout << "[";
	for (int i = 0; i < resource->size(); i++)
	{
		if(i == resource->size() - 1)
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