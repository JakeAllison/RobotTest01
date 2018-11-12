//============================================================================
// Name        : CodeBaseTest.cpp
// Author      : Jake
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#define WAIT_FOR_ENTER_PRESS std::cin.ignore();

#include <iostream>
using namespace std;
#include <Test/TestTask.h>
#include <Test/TestData.h>
#include <Test2/Test2Task.h>

int main()
{
    frc::TestData testData;
    frc::TestTask testTask(&testData);
    frc::Test2Task test2Task(&testData);
    testTask.Start(1000000);
    test2Task.Start(333333);

    int temp1 = 0;
    double temp2 = 0;
    int temp3 = 0;
    double temp4 = 0;
    int temp5 = 0;
    double temp6 = 0;

    while (true)
    {
    	//------------------------------------------------------------------------------------------
    	//                                 Main Program Demo
    	//------------------------------------------------------------------------------------------
    	//
    	// This is a demonstration of the multithreading and data-checking abilities of this program.
    	// This loop can act in place of a worker thread, or in place of a "Master" thread to test
    	//     the abilities of Worker threads and of the custom data structures.
    	// The user simply presses the Enter key and the variables below get updated and the data
    	// is sent to the shared data structure.
    	//
    	//------------------------------------------------------------------------------------------
    	//                                 Worker Thread Functionality
    	//------------------------------------------------------------------------------------------
    	//
    	// Worker threads are created to carry out a specific task completely independently.
    	// These are created with the "ThreadTaskBase" class.
    	// In this example, a worker object, "testTask", is running it's own periodic task,
    	//     which updates a couple variables and calls a function ThreadTaskBase::PrintData()
    	//     for the data structure to print out all the data stored.
    	// The robot can have several tasks running simultaneously, and they all can read from
    	//      a set of common data structures.
    	//
    	//------------------------------------------------------------------------------------------
    	//                                 Data Structure Functionality
    	//------------------------------------------------------------------------------------------
    	//
    	// These data structures, based on the "ThreadDataBase" class, are the main source of
    	//     inter-thread data sharing and storage. These data classes will usually have an
    	//     associated "Friend" class that is a derived worker thread class. That friend class
    	//     should be the only thing that actually writes data to the data structure.
    	// More advanced features can include sending a specific request for a thread to take an action,
    	//     such as Reset_Gyro_Heading(), Turn_On_Intake_Until_Current_Spike_Detected(), Reset_Encoders(), etc.
    	// These can be categorized as "On-Demand" functionality, rather than periodically updated data which is
    	//     the main form of data storage and communication.
    	// One of these data structures will usually contain several Data Arrays as explained below.
    	// Each array would be made for different data types needed.
    	//
    	//------------------------------------------------------------------------------------------
    	//                                 Data Array Functionality
    	//------------------------------------------------------------------------------------------
    	//
    	// All data is stored in data array structures. They all have mutex locks to make sure multiple threads can play nicely.
    	// These locks are implemented in the Set(), Get(), AddKey() and RemoveKey() functions.
    	// Threre are four such structures supporting int and double:
    	//
    	// 1) MultithreadDataArray<int>            // Stores data if the key exists.
    	// 2) MultithreadDataArray<double>         // Stores data if the key exists.
    	// 3) SafeMultithreadDataArray<int>        // Stores data if the key exists. Can perform range checking and determine if data is 'stale'.
    	// 4) SafeMultithreadDataArray<double>     // Stores data if the key exists. Can perform range checking and determine if data is 'stale'.
    	//
    	// These structures store data in their respective unordered_maps as such below. This can be expanded later
    	//     to accomodate different data types if needed:
    	//
    	// 1) unordered_map<std::string, int>
    	// 2) unordered_map<std::string, double>
    	// 3) unordered_map<std::string, SafeData<int>>
    	// 4) unordered_map<std::string, SafeData<double>>
    	//
    	//------------------------------------------------------------------------------------------
    	//                                 Safe Data Functionality
    	//------------------------------------------------------------------------------------------
    	//
    	// The "SafeData" class is a class for safety-critical data that needs to be a) in-range, and b) recently updated.
    	//
    	// The SafeData class is meant to contain a single piece of data that has its own characteristics:
    	//
    	// 1) Range Min/Max: Maximum range. Setting these to the same value disables range-checking.
    	// 2) Data Update Timeout: The maximum amount of time the data needs to be updated before becoming "stale".
    	//        Data that is stale was not updated recently enough.
    	//
    	// 3) Validity: Status of the piece of data. This can have 4 states:
    	//        0) Valid: Good data, in range, and updated recently.
    	//        1) Invalid: Data that was not updated recently enough.
    	//        2) Degraded: Data that is out-of range. This needs to be forced, otherwise the data isn't updated.
    	//        3) Test: Data is a test value and is not affected by range checking or staleness.
    	//
    	// When the function is called to Set() data:
    	//     1) Good data will be updated. DATA_VALIDITY_VALID will be returned.
    	//     2) Any data that is out-of-range will not be updated unless forced. DATA_VALIDITY_DEGRADED will be returned.
    	//     3) Data with the "IsTest" flag set will automatically update, and DATA_VALIDITY_TEST will be returned.
    	//
    	// When the function is called to Get() data:
    	//     1) Good data will be retrieved. DATA_VALIDITY_VALID will be returned.
    	//     2) Any data that is out-of-range will not be retrieved unless forced. DATA_VALIDITY_INVALID will be returned.
    	//     3) Data with the "IsTest" flag set will NOT get retrieved unless forced, and DATA_VALIDITY_TEST will be returned.
    	//     4) If the data not successfully updated recently enough will NOT be retrieved unless forced, and DATA_VALIDITY_INVALID returned.
    	//
    	//------------------------------------------------------------------------------------------
    	//                                    To Run This Demo
    	//------------------------------------------------------------------------------------------
    	//
    	// The different characteristics of these features is explained in the constructor definition in "TestTask.cpp".
    	// The data for all the keys, named "Key 1" through "Key 6" all demonstrate different abilities.
    	//
    	// Some things you will need to know about the console output:
    	// 1) Every time the PrintData() function is called, each piece of data is displayed as such:
    	//
    	// For regular outputs, just the unordered_map key and it's data are displayed:
    	//      <Key>: <Data Value>
    	//
    	// For SafeData outputs, the unordered_map key, data validity, and it's data are displayed:
    	//      <Key>: <Validity>, <Data Value>
    	//
    	// The enumeration for the validity is explained above.
    	//     - 0=Valid, 1=Invalid, 2=Degraded, 3=Test
    	//
    	// An example is shown here:
    	//    > Shared Key: 484107       // Both the user and worker thread can modify this.
    	//    > Key 1: 107
    	//    > UserCountKey: 107        // The user increments this with every key press.
    	//    > ThreadCountKey: 484      // The worker thread increments this periodically.
    	//    > Key 2: 35.631
    	//    > Key 5: 1, 2              // Invalid. The value shown is NOT necessarily what is contained in the data structure.
    	//    > Key 3: 0, 2              // Valid. No range or update checking checking was applied.
    	//    > Key 6: 1, 4.896          // Invalid. The value shown is NOT necessarily what is contained in the data structure.
    	//    > Key 4: 2, -6.75          // Valid. No range or update checking checking was applied.
    	//    > Thread 2: 1              // Data is being displayed on the Test2Task thread.
    	//    > Thread 2: 1              // Data is being displayed on the Test2Task thread.
    	//    > Set() Degraded: Input 5, Key 5      // The user just tried to enter out-of-range data on the "Master" thread.

        WAIT_FOR_ENTER_PRESS

        temp1 += 1;
        temp2 += 0.333;
        temp3 = ((temp3 < 10) ? (temp3 + 1) : -10);
        temp4 = ((temp4 < 10.0) ? (temp4 + 0.5) : -10.0);
        temp5 = ((temp5 < 10) ? (temp5 + 1) : -10);
        temp6 = ((temp6 < 10.0) ? (temp6 + 0.4) : -10.0);

        testData.SetDataManual("Key 1", temp1, "Input 1");
        testData.SetDataManual("Key 2", temp2, "Input 2");
        testData.SetSafeDataManual("Key 3", temp3, "Input 3", false, true);
        testData.SetSafeDataManual("Key 4", temp4, "Input 4");
        testData.SetSafeDataManual("Key 5", temp5, "Input 5");
        testData.SetSafeDataManual("Key 6", temp6, "Input 6", true, false);

        int temp2 = -0xFFFF;
        testData.GetData("Shared Key", temp2, "Thread Task");
        temp2 += 1;
        testData.SetDataManual("Shared Key", temp2, "Thread Task");

        int tempCount = -0xFFFF;
        testData.GetData("UserCountKey", tempCount);
        tempCount++;
        testData.SetDataManual("UserCountKey", tempCount);
        //Sleep(1500);
    }
    return 0;
}
