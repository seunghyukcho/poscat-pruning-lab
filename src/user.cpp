#include <climits>
#include <algorithm>
#include "tester.h"
#define MAX_DEPTH 7

using namespace std;

void copyArray(int dest[][6], int src[][6]);
int isTerminalNode(int board[][6]);
void simulation(int state[][6], Action& action, int player);
int pruning(int state[][6], int depth, int alpha, int beta, int player);

Action ans;

/**
 * @brief
 * You should implement this function with alpha-beta pruning.
 * The problem is that you have to find the best action to maximize the score.
 * You should use the scoring function in Tester class.
 * Have a good coding!
 * @param board The input testcase that you should use. The index starts from 1, not 0, and ends at 5.
 * @param answer
 * Parameter for your answer. The definition is in includes/utility.h
 * You should modify it to be your answer. Please see the sample code if it is hard to understand.
 * You have to implement a depth 7 alpha-beta pruning to get correct answer.
 * If there are several solutions, you can just pick one of them.
 */
void Tester::solve(int board[][6], Action& answer)
{
	int result = pruning(board, MAX_DEPTH, -1e9 - 1, 1e9 + 1, 1);
	answer = ans;
}

void copyArray(int dest[][6], int src[][6])
{
	for(int i = 1; i < 6; i++)
		for(int j = 1; j < 6; j++)
			dest[i][j] = src[i][j];
}

int isTerminalNode(int board[][6])
{
	bool flag;
	for(int i = 1; i < 6; i++)
	{
		flag = board[i][1] != 0;
		for(int j = 1; flag && j < 6; j++)
			if(board[i][j] != board[i][1])
				flag = false;
		if(flag)
			return board[i][1];
	}

	for(int i = 1; i < 6; i++)
	{
		flag = board[1][i] != 0;
		for(int j = 1; flag && j < 6; j++)
			if(board[j][i] != board[1][i])
				flag = false;
		if(flag)
			return board[1][i];
	}

	flag = board[1][1] != 0;
	for(int i = 1; flag && i < 6; i++)
		if(board[i][i] != board[1][1])
			flag = false;
	if(flag)
		return board[1][1];

	flag = board[5][1] != 0;
	for(int i = 1; flag && i < 6; i++)
		if(board[6 - i][i] != board[5][1])
			flag = false;
	if(flag)
		return board[5][1];

	return 0;
}

void simulation(int state[][6], Action& action, int player)
{
	int dir[4][2] = { 0, -1, -1, 0, 0, 1, 1, 0 };
	int dirx = dir[action.dir][0], diry = dir[action.dir][1];
	int herex = action.x, herey = action.y;

	while(1)
	{
		int nextx = herex + dirx, nexty = herey + diry;
		if(nextx < 1 || nexty < 1 || nextx > 5 || nexty > 5)
			break;
		state[herex][herey] = state[nextx][nexty];
		herex += dirx, herey += diry;
	}

	state[herex][herey] = player;
}

int pruning(int state[][6], int depth, int alpha, int beta, int player)
{
	if(depth == 0 || isTerminalNode(state))
		return Tester::scoring(state);

	bool flag = true;
	int v = (player == 1 ? -1e9 - 1 : 1e9 + 1);
	int here[4][2] = { 2, 1, 5, 2, 4, 5, 1, 4 };
	int dir[4][2] = { 1, 0, 0, 1, -1, 0, 0, -1 };
	int nextState[6][6];

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			int herex = here[j][0] + dir[j][0] * i, herey = here[j][1] + dir[j][1] * i;

			if((state[herex][herey] | player) != 3)
			{
				for(int k = 0; k < 4; k++)
				{
					if(herex == 1 && k == 1) continue;
					if(herey == 1 && k == 0) continue;
					if(herex == 5 && k == 3) continue;
					if(herey == 5 && k == 2) continue;

					Action action = { herex, herey, k };
					copyArray(nextState, state);
					simulation(nextState, action, player);
					int result = pruning(nextState, depth - 1, alpha, beta, player % 2 + 1);

					if(player == 1)
					{
						if(depth == MAX_DEPTH && v < result)
							ans = action;
						
						v = max(v, result);
						alpha = max(alpha, v);
					}
					else
					{
						v = min(v, result);
						beta = min(beta, v);
					}

					if(beta <= alpha)
						return v;
				}
			}
		}
	}

	return v;
}