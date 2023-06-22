#include <iostream>
#include <thread>
#include "Control/control.h"
using namespace std;

ControlAPI* control = new ControlAPI(10);

int main()
{
	control->initialize();
	std::thread Thread1(&ControlAPI::write, control, 1);
	std::thread Thread2(&ControlAPI::read, control, 2);

	Thread1.join();
	Thread2.join();
	printBuffer(control->getWriteIndex(), control->getSharedResourcePtr());
	return 0;
}