#pragma once
#include <iostream>
#include <vector>
using namespace std;

// The buffer has a maximum size that is constant
const int maxBufferSite = 10;

// Write data to the shared resource
void write(int value);

// Read and consume data from the share resource
void read();

// Initialize the shared resource
vector<int>* initialize();

int generateRandomNumber(); //ToDo GOES INTO HELPER/UTILS
void sleepFor(int seconds); //ToDo GOES INTO HELPER/UTILS
void printBuffer(vector<int>* resource);
