#include <iostream>
#include <random>
#include <chrono>
#include "control.h"

using namespace std;

/*
 * Constructor for the ControlAPI class.
 * This constructor initializes an instance of the ControlAPI class with the specified size.
 * It validates that the size is greater than 0 and sets the maximum buffer size accordingly.
 *
 * @param size The size of the shared resource buffer.
 */
ControlAPI::ControlAPI(int size)
{
	if (size <= 0) // Check if the size is less than or equal to 0
	{
		std::cerr << "Size must be greater than 0!" << std::endl; // Print an error message if the size is invalid
	}

	this->maxBufferSize = size; // Set the maximum buffer size to the specified size
}

/*
 * This function is responsible for initializing the shared resource, which is a
 * vector of pointers to Data struct objects. It allocates memory for the vector with the specified
 * maximum buffer size. If memory allocation fails, an error message is printed.
 */
void ControlAPI::initialize()
{
	this->sharedResourcePtr = new vector<Data*>(this->maxBufferSize); // Allocate memory for the shared resource vector

	if (this->sharedResourcePtr == nullptr) // Check if memory allocation failed
	{
		std::cerr << "Unable to allocate shared resource!"; // Print an error message if memory allocation failed
	}
}


/*
 * Writes data to the shared resource.
 *
 * This function is responsible for writing data to the shared resource.
 * It generates random data, assigns it to a new instance of the Data struct,
 * and stores it in the shared resource buffer. The function uses a 
 * mutex and condition variables to synchronize access to the shared resource
 * and to ensure that the buffer is not full before writing.
 *
 * @param threadNum The thread number indicating the calling thread.
 */
void ControlAPI::write(int threadNum)
{
	int writeOperationCounter = 0; // Counter for the number of write operations
	while (writeOperationCounter++ != this->maxOperationsNum) // Loop until the desired number of write operations is reached
	{
		std::unique_lock<std::mutex> lock(this->controlMutex); // Acquire a unique lock on the ControlAPI instance mutex

		int nextWriteIndex = (this->currentWriteIndex + 1) % maxBufferSize; // Calculate the next write index in the circular buffer

		// Wait until the buffer is not full before proceeding with the write operation
		/*
		 * The lambda function is a predicate that takes the next
		 * index to write and the pointer to the ControlAPI instance.
		 * Return true if the buffer is not full or false if it is full.
		 */ 
		this->bufferIsFull.wait(lock, [nextWriteIndex, this] { return nextWriteIndex != this->currentReadIndex; });

		Data* dataToWrite = new Data; // Create a new instance of the Data struct
		dataToWrite->dataInt1 = generateRandomNumber(1, 10); // Generate first random int value
		dataToWrite->dataInt2 = generateRandomNumber(1, 10); // Generate second random int value
		cout << "Thread[" << threadNum << "] Writing at index [" << this->currentWriteIndex << "]: " << dataToWrite->dataInt1 << endl;

		this->sharedResourcePtr->at(this->currentWriteIndex) = dataToWrite; // Store the data in the shared resource buffer at the current write index
		this->currentWriteIndex = nextWriteIndex; // Update the current write index to the next index in the circular buffer
		lock.unlock(); // Release the lock on the control mutex

		this->bufferIsEmpty.notify_one(); // Notify waiting threads that the buffer is no longer empty
	}
}

/*
 * Reads data from the shared resource.
 *
 * This function is responsible for reading data from the shared resource.
 * It retrieves the data from the shared resource buffer, prints it to the console and deallocates it.
 * The function uses a control mutex and condition variables
 * to synchronize access to the shared resource and to ensure that the buffer
 * is not empty before reading.
 *
 * @param threadNum The thread number indicating the calling thread.
 */
void ControlAPI::read(int threadNum)
{
	int readOperationCounter = 0; // Counter for the number of read operations
	while (readOperationCounter++ != this->maxOperationsNum) // Loop until the desired number of read operations is reached
	{
		// Simulate a delay to emulate faster writing than reading
		sleepFor(threadNum, 100);

		std::unique_lock<std::mutex> lock(this->controlMutex); // Acquire a unique lock on the control mutex

		int nextReadIndex = (this->currentReadIndex + 1) % maxBufferSize; // Calculate the next read index in the circular buffer

		// Wait until the buffer is not empty before proceeding with the read operation
		/*
		 * The lambda function is a predicate that takes the pointer to the ControlAPI instance.
		 * Return true if the buffer is not empty or false if it is empty.
		 */
		this->bufferIsEmpty.wait(lock, [this] { return this->currentReadIndex != this->currentWriteIndex; });

		Data* consumedValue = this->sharedResourcePtr->at(this->currentReadIndex); // Retrieve the data from the shared resource buffer at the current read index
		cout << "Thread[" << threadNum << "] Reading at index [" << this->currentReadIndex << "]: " << consumedValue->dataInt1 << endl;
		delete consumedValue; // Deallocate the consumed data object

		this->currentReadIndex = nextReadIndex; // Update the current read index to the next index in the circular buffer
		lock.unlock(); // Release the lock on the control mutex

		this->bufferIsFull.notify_one(); // Notify waiting threads that the buffer is no longer full
	}
}

