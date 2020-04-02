/*************************************************************************
	> File Name: utility.h
	> Author: wangpeizhen
	> Mail: 
	> Created Time: 四  4/ 2 14:54:03 2020
 ************************************************************************/

#ifndef _UTILITY_H
#define _UTILITY_H
#pragma once
#include "Expression.h"
int IsLarger(BinaryOperator B1, BinaryOperator B2);
bool Is(const char*& Stream, const char* Text);
int Regular(int input);
char GetOp(BinaryOperator B);

struct Exception {
	const char* Start;
	const char* Error;

	Exception(const char* aStart, const char* aError) {
		Start = aStart;
		Error = aError;
	}
};
#endif
