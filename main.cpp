#include <iostream>
#include <thread>
#include "Control/control.h"
using namespace std;

vector<int>* sharedResource = initialize();
int main()
{
	
	std::thread Thread1(write, sharedResource);
	std::thread Thread2(read, sharedResource);

	Thread1.join();
	Thread2.join();
	printBuffer(sharedResource);
	return 0;
}