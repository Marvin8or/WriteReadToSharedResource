#include <iostream>
#include <thread>
#include "Control/control.h"
#include "Utils/utils.h"
using namespace std;

ControlAPI* control = new ControlAPI(10);

//TODO Test code

int main()
{
	control->initialize();

	// --------------------
	// |***** Test 1 *****|
	// --------------------
	/*
	 * Test execution when both threads execute with approximately same time
	 * On my PC, range of avg. execution time is [1.6 - 2.5] ms without added delay.
	 * The point is that both function take same time to execute.
	 */
	//std::thread Thread1(&ControlAPI::write, control, 1, 0);
	//std::thread Thread2(&ControlAPI::read, control, 2, 0);

	//Thread1.join();
	//Thread2.join();

	//printBuffer(control->getWriteIndex(), control->getSharedResourcePtr());

	// --------------------
	// |***** Test 2 *****|
	// --------------------
	/*
	 * Test execution when write is faster than read
	 * Problem: If the write methods is much faster than the read method, the read method spends lots of time waiting for the
	 * write method. 
	 */
	//std::thread Thread1(&ControlAPI::write, control, 1, 10);
	//std::thread Thread2(&ControlAPI::read, control, 2, 100);

	//Thread1.join();
	//Thread2.join();

	//printBuffer(control->getWriteIndex(), control->getSharedResourcePtr());

	// --------------------
	// |***** Test 3 *****|
	// --------------------
	/*
	 * Test execution when read is faster than write
	 * Read method cosumes the new data immediately after write operation
	 */
	 //std::thread Thread1(&ControlAPI::write, control, 1, 100);
	 //std::thread Thread2(&ControlAPI::read, control, 2, 10);

	 //Thread1.join();
	 //Thread2.join();

	 //printBuffer(control->getWriteIndex(), control->getSharedResourcePtr());
	return 0;
}