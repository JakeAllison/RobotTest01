/*
 * Test2Task.h
 *
 *  Created on: Nov 11, 2018
 *      Author: Jake
 */

#ifndef TEST2_TEST2TASK_H_
#define TEST2_TEST2TASK_H_

#include <ThreadBases/ThreadTaskBase.h>
#include <Test/TestData.h>


namespace frc
{

class Test2Task : public ThreadTaskBase
{
public:
    Test2Task(TestData* testData);
    virtual ~Test2Task();
private:
    TestData* _testData;
    void ThreadTask() override;
};

} /* namespace frc */

#endif /* TEST2_TEST2TASK_H_ */
