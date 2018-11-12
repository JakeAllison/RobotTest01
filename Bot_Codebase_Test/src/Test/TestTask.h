/*
 * TestTaskData.h
 *
 *  Created on: Nov 10, 2018
 *      Author: Jake
 */

#ifndef TEST_TESTTASK_H_
#define TEST_TESTTASK_H_

#include <Test/TestData.h>
#include <ThreadBases/ThreadTaskBase.h>

namespace frc
{

class TestTask : public ThreadTaskBase
{
public:
    TestTask(TestData* testData);
    virtual ~TestTask();
private:
    TestData* _testData;
    void ThreadTask() override;
};

} /* namespace frc */

#endif /* TEST_TESTTASK_H_ */
