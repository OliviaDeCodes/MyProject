/*************************************************************************
	> File Name: visitor.h
	> Author: wangpeizhen
	> Mail: 
	> Created Time: 四  4/ 2 14:54:25 2020
 ************************************************************************/

#ifndef _VISITOR_H
#define _VISITOR_H
#pragma once
#include "Expression.h"
#include "utility.h"
#include <string>
#include <stack>
using std::string;
using std::stack;
using std::to_string;


class ExpressionPointer :public Expression::IVisior {
public:
	string result;
    int level;

	void Visit(NumberExpression* node);



	void Visit(BinaryExpression* node);

};
#endif
