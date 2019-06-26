#include "tester.h"

/**
 * @brief
 * You should implement this function with alpha-beta pruning.
 * The problem is that you have to find the best action to maximize the score.
 * You should use the scoring function in Tester class.
 * Have a good coding!
 * @param board The input testcase that you should use. The index starts from 1, not 0, and ends at 5.
 * @param 
 * Parameter for your answer. The definition is in includes/utility.h
 * You should modify it to be your answer. Please see the sample code if it is hard to understand.
 * You have to implement a depth 7 alpha-beta pruning to get correct answer.
 * If there are several solutions, you can just pick one of them.
 */
void Tester::solve(int board[][6], Action& answer)
{
	// Please replace the code under with yours.
	int stateScore = Tester::scoring(board); // You can use scoring function from Tester class like this!

	answer.x = 1; 
	answer.y = 1;
	answer.dir = 1; // this means pop (1, 1) block and push in the 1 direction.	
}
