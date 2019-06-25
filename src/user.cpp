#include "tester.h"
#include <unistd.h>

/**
 * @brief
 * You should implement this function with alpha-beta pruning.
 * The problem is that you have to find the best action to maximize the score.
 * You should use the scoring function in Tester class.
 * Have a good coding!
 * @param testCase The input testcase that you should use. The definition is in includes/utility.h
 * @param 
 * Parameter for your answer. The definition is in includes/utility.h
 * You should modify it to match your answer. Please see the sample code if it is hard to understand.
 */
void Tester::solve(TestCase testCase, Action& answer)
{
	// Please replace the code under with yours.
	answer.x = 1; 
	answer.y = 1;
	answer.dir = 1; // this means pop (1, 1) block and push in the 1 direction.
}