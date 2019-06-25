#ifndef UTILITY__H
#define UTILITY__H

struct Action
{
	int x, y;
	int dir;

	bool operator==(const Action& operand)
	{
		return this->x == operand.x && 
			this->y == operand.y &&
			this->dir == operand.dir;
	}
};

struct TestCase
{
	int board[6][6];
};

#endif