#include <iostream>
#include <thread>
#include "Control/control.h"
using namespace std;

vector<int>* sharedResource = initialize();
std::mutex controlMutex;

int currReadIndex = 0;
int currWriteIndex = 0;

int main()
{
	
	std::thread Thread1(write, 1, std::ref(controlMutex), sharedResource, std::ref(currReadIndex), std::ref(currWriteIndex));
	std::thread Thread2(read, 2, std::ref(controlMutex), sharedResource, std::ref(currReadIndex), std::ref(currWriteIndex));

	Thread1.join();
	Thread2.join();
	printBuffer(sharedResource);
	return 0;
}