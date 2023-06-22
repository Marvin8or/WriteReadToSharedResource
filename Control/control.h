#pragma once
#include <iostream>
#include <vector>
#include <mutex>
using namespace std;

// The buffer has a maximum size that is constant
const int maxBufferSize = 10;

// Maximum number fo read/write operations
const int maxOperations = 100;

// Write data to the shared resource
void write(int threadNum, std::mutex& m, vector<int>* sharedResource, int& readIndex, int& writeIndex);

// Read and consume data from the share resource
void read(int threadNum, std::mutex& m, vector<int>* sharedResource, int& readIndex, int& writeIndex);

// Initialize the shared resource
vector<int>* initialize();

int generateRandomNumber(int min_val, int max_val); //ToDo GOES INTO HELPER/UTILS
void sleepFor(int threadNum, int value); //ToDo GOES INTO HELPER/UTILS
void printBuffer(vector<int>* resource);
