/*************************************************************************
	> File Name: testcase2.h
	> Author: wpz
	> Mail: 1024827983@qq.com
	> Created Time: 日 10/ 7 11:41:30 2018
 ************************************************************************/
#ifndef _TESTCASE2_H
#define _TESTCASE2_H
#include "test.h"
#include "newton.h"

TEST(test, newton_func) {
        EXPECT(newton(2), 1.0);
        EXPECT(newton(4), 2.0);
        EXPECT(newton(10), 4);
        EXPECT(newton(25), 5);
}


#endif
