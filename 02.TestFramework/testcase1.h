/*************************************************************************
	> File Name: testcase1.h
	> Author: wpz
	> Mail: 1024827983@qq.com
	> Created Time: 日 10/ 7 11:40:48 2018
 ************************************************************************/
#ifndef _TESTCASE1_H
#define _TESTCASE1_H
#include "test.h"
#include "two_points.h"

TEST(test, two_points_func) {
    for (int i = -10; i <= 110; i += 2) {
    EXPECT(two_points(i, 2 * i, i/2), 1);       
 }
}


#endif
