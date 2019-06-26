#ifndef UTILITY__H
#define UTILITY__H

/**
 * @struct 
 * Structure of Action. 
 * (x, y) means the block going be popped.
 * dir means the direction going to be insert. 
 * 0 - left, 1 - up, 2 - right, 3 - down.
 * In some positions, some of the directions are blocked.
 */
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

/**
 * @struct 
 * Structure of TestCase. 
 * board is the present state.
 * 0 - nothing, 1 - yours, 2 - enemies.
 */
struct TestCase
{
	int board[6][6];
};

#endif
