#include <iostream>
#include <thread>
#include "Control/control.h"
using namespace std;

vector<int>* sharedResource = initialize();
std::mutex controlMutex;
int counter = 0;

int main()
{
	
	std::thread Thread1(write, 1, std::ref(controlMutex), sharedResource, std::ref(counter));
	std::thread Thread2(read, 3, std::ref(controlMutex), sharedResource, std::ref(counter));

	Thread1.join();
	Thread2.join();
	printBuffer(sharedResource, &counter);
	return 0;
}