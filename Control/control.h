#pragma once
#include <iostream>
#include <vector>
using namespace std;

// The buffer has a maximum size that is constant
const int maxBufferSite = 10;

// Maximum number fo read/write operations
const int maxOperations = 100;

// Write data to the shared resource
void write(vector<int>* sharedResource);

// Read and consume data from the share resource
void read(vector<int>* sharedResource);

// Initialize the shared resource
vector<int>* initialize();

int generateRandomNumber(int min_val, int max_val); //ToDo GOES INTO HELPER/UTILS
void sleepFor(int seconds); //ToDo GOES INTO HELPER/UTILS
void printBuffer(vector<int>* resource);
