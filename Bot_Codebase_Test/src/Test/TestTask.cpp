/*
 * TestTaskData.cpp
 *
 *  Created on: Nov 10, 2018
 *      Author: Jake
 */

#include <Test/TestTask.h>
#include <iostream>
namespace frc
{

TestTask::TestTask(TestData* testData):
        _testData(testData)
{
	// ThreadCountKey demonstrates  the worker thread's ability to  update data.
    _testData->AddKey<int>("ThreadCountKey");

	// UserCountKey demonstrates the ability of other threads to  update data.
    _testData->AddKey<int>("UserCountKey");

    // Demonstration of data storage without range limitaions or minimum update periods.
    _testData->AddKey<int>("Key 1");
    _testData->AddKey<double>("Key 2");

    // Demonstration of "Safe" data storage with no limits set.
    _testData->AddSafeKey<int>("Key 3");
    _testData->AddSafeKey<double>("Key 4");

    // Demonstration of "Safe" data storage with:
    // 1) Range checking. This will not update out-of-range values unless forced.
    // 2) Data "Validity" requires that the data be updated every so often, or else the data is marked as stale, or "Invalid".
    //
    // These examples use ranges [-6, 6] and [-5, 5].
    // The timeouts were set to 2,000,000 microseconds, or 2 seconds.
    _testData->AddSafeKey<int>("Key 5", 0, -6, 6, 2000000);
    _testData->AddSafeKey<double>("Key 6", 0, -5, 5, 2000000);

    // This demonstrates the ability of both threads to share common data.
    // Only the "owner" thread should be able to write to this and it is discouraged to have
    //     multiple thread writing to the same data structure, but reading and writing can be done.
    // That's why the "TestTask" class is a friend of "TestData".
    _testData->AddKey<int>("Shared Key");
}

TestTask::~TestTask()
{
    // TODO Auto-generated destructor stub
}

void TestTask::ThreadTask()
{

	// This function reads the data, does some processing on the data, then writes the data back.
	// This is done for both it's own data, and the shared data.

    int temp1 = -0xFFFF;
    _testData->GetData("ThreadCountKey", temp1, "Thread Task");
    temp1++;
    _testData->SetData("ThreadCountKey", temp1, "Thread Task");

    int temp2 = -0xFFFF;
    _testData->GetData("Shared Key", temp2, "Thread Task");
    temp2 += 1000;
    _testData->SetData("Shared Key", temp2, "Thread Task");

    _testData->PrintData();
}

} /* namespace frc */
