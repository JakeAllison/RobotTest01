/*
 * Test2Data.h
 *
 *  Created on: Nov 11, 2018
 *      Author: Jake
 */

#ifndef TEST2_TEST2DATA_H_
#define TEST2_TEST2DATA_H_

#include <ThreadBases/ThreadDataBase.h>


namespace frc
{

class Test2Data : public ThreadDataBase
{
public:
	friend class Test2DTask;
    Test2Data();
    virtual ~Test2Data();
};

} /* namespace frc */

#endif /* TEST2_TEST2DATA_H_ */
