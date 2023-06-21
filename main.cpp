#include <iostream>
#include <thread>
#include "Control/control.h"
using namespace std;

vector<int>* sharedResource = initialize();
int main()
{
	
	std::thread Thread1(write, 123);
	std::thread Thread2(read);

	Thread1.join();
	Thread2.join();
	printBuffer(sharedResource);
	return 0;
}