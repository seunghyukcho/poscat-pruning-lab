#ifndef TESTER__H
#define TESTER__H
#include <iostream>
#include <algorithm>
#include <vector>
#include "utility.h"

class Tester
{
private:
	std::vector<TestCase> testCases;
	std::vector<std::vector<Action> > solutions;

public:
	Tester(int testCaseNumber);
	void importTestCase(int testCaseNumber);
	void testAll();
	int test(int testCaseNumber);
	void solve(int board[][6], Action& answer);
	static int scoring(int board[][6]);
};

#endif
