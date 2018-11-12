/*
 * Test2Task.cpp
 *
 *  Created on: Nov 11, 2018
 *      Author: Jake
 */

#include <Test2/Test2Task.h>
#include <iostream>

namespace frc
{

Test2Task::Test2Task(TestData* testData):
                _testData(testData)
{
    // TODO Auto-generated constructor stub

}

Test2Task::~Test2Task()
{
    // TODO Auto-generated destructor stub
}


void Test2Task::ThreadTask()
{

	// This task reads one of the variables in the data from the other thread.
	int temp = -0xFFFF;
	_testData->GetSafeData("Key 5", temp,"", true, true, true);
	std::cout << "Thread 2: " << temp << std::endl;


}

} /* namespace frc */
