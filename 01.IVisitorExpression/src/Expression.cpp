/*************************************************************************
	> File Name: Expression.cpp
	> Author: wangpeizhen
	> Mail: 
	> Created Time: 四  4/ 2 14:54:59 2020
 ************************************************************************/

#include "Expression.h"

Expression::Expression() {
	IsLeft = false;
}

void NumberExpression::Accept(IVisior* visitor) {
	visitor->Visit(this);
}

NumberExpression::NumberExpression(int number) {
	Value = number;
}

void BinaryExpression::Accept(IVisior* visitor) {
	visitor->Visit(this);
}

