/*
 * TestData.h
 *
 *  Created on: Nov 10, 2018
 *      Author: Jake
 */

#ifndef TEST_TESTDATA_H_
#define TEST_TESTDATA_H_

#include <ThreadBases/ThreadDataBase.h>
#include <string>


namespace frc
{

class TestData : public ThreadDataBase
{
public:
    friend class TestTask;
    TestData();
    virtual ~TestData();
    void SetDataManual(std::string datakey, int inputdata, std::string contextmessage = "")
    {
        SetData(datakey, inputdata, contextmessage);
    }
    void SetDataManual(std::string datakey, double inputdata, std::string contextmessage = "")
    {
        SetData(datakey, inputdata, contextmessage);
    }
    void SetSafeDataManual(std::string datakey, int inputdata, std::string contextmessage = "", bool isTest = false, bool forceIfDegraded = false)
    {
        SetSafeData(datakey, inputdata, contextmessage, isTest, forceIfDegraded);
    }
    void SetSafeDataManual(std::string datakey, double inputdata, std::string contextmessage = "", bool isTest = false, bool forceIfDegraded = false)
    {
        SetSafeData(datakey, inputdata, contextmessage, isTest, forceIfDegraded);
    }
};

} /* namespace frc */

#endif /* TEST_TESTDATA_H_ */
