#include "tester.h"
#include <vector>
#define ENEMY(player) (3-(player))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

using namespace std;

void move(int board[6][6], int x, int y, int dir, int turn){
	int save = turn;
	if(dir == 0){//left
		for(int i=y;i>1;--i){
			board[x][i] = board[x][i-1];
		}
		board[x][1] = save;
	}
	else if(dir == 1){//up
		for(int i=x;i>1;--i){
			board[i][y] = board[i-1][y];
		}
		board[1][y] = save;
	}
	else if(dir == 2){//right
		for(int i=y;i<5;++i){
			board[x][i] = board[x][i+1];
		}
		board[x][5] = save;
	}
	else{//down
		for(int i=x;i<5;++i){
			board[i][y] = board[i+1][y];
		}
		board[5][y] = save;
	}
}
void same(int save[6][6], int board[6][6]){
	for(int i=1;i<=5;++i){
		for(int j=1;j<=5;++j){
			save[i][j]=board[i][j];
		}
	}
}

bool fin(int board[6][6]){
	int num[3]={0};
	for(int i=1;i<=5;++i){
		num[1]=num[2]=0;
		for(int j=1;j<=5;++j){
			num[board[i][j]]++;
		}
		for(int k=1;k<=2;++k){
			if(num[k]==5) return true;
			num[k]=0;
		}


		for(int j=1;j<=5;++j){
			num[board[j][i]]++;
		}
		for(int k=1;k<=2;++k){
			if(num[k]==5) return true;
			num[k]=0;
		}
	}
	for(int j=1;j<=5;++j){
		num[board[j][j]]++;
	}
	for(int k=1;k<=2;++k){
		if(num[k]==5) return true;
		num[k]=0;
	}

	for(int j=1;j<=5;++j){
		num[board[j][6-j]]++;
	}
	for(int k=1;k<=2;++k){
		if(num[k]==5) return true;
		num[k]=0;
	}

	return false;
}

int ab_solve(int board[6][6], int a, int b, int turn, int depth){
	if(depth==0 || fin(board)) return Tester::scoring(board);


	int save_board[6][6]={0};
	same(save_board,board);
	int res;
	vector<int> list;

	int v;
	if(turn == 1) v = -1e9;
	else v = 1e9;


	for(int i=1;i<=5;++i){
		for(int j=1;j<=5;++j){
			if( !((i==1 || i==5)&&(j==1||j==5)) ) continue;

			list.clear();
			if(board[i][j] != ENEMY(turn)){
				if(i != 1)
					list.push_back(1);
				if(i != 5)
					list.push_back(3);
				if(j != 1)
					list.push_back(0);
				if(j != 5)
					list.push_back(2);
			}

			for(int iter=0;iter<list.size();++iter){
				move(board,i,j,list[iter], turn);
				res = ab_solve(board, a, b, ENEMY(turn), depth-1);
				same(board,save_board);

				if(turn == 1){
					v = MAX(v,res);
					a = MAX(a,v);
					if(a>=b)
						return v;
				}
				else{
					v = MIN(v,res);
					b = MIN(v,b);
					if(a>=b)
						return v;
				}
			}



		}
	}
	return v;
}

struct ACT{
	int x,y,dir;
	ACT(int _x, int _y, int _dir){
		x = _x;
		y = _y;
		dir = _dir;
	}
};

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
	int max_depth = 7;
	int save_board[6][6];
	int max_v = -1e9 - 1;
	vector<int> list;

	same(save_board, board);

	for(int i=1;i<=5;++i){
		for(int j=1;j<=5;++j){
			if( !((i==1 || i==5)||(j==1||j==5)) ) continue;

			list.clear();
			if(board[i][j] != 2){
				if(i != 1)
					list.push_back(1);
				if(i != 5)
					list.push_back(3);
				if(j != 1)
					list.push_back(0);
				if(j != 5)
					list.push_back(2);
			}

			for(int iter=0;iter<list.size();++iter){
				move(board,i,j,list[iter], 1);
				int val = ab_solve(board, -1e9, 1e9, 2, max_depth-1);
				same(board,save_board);

				if(val > max_v){
					max_v = val;
					answer.x = i;
					answer.y = j;
					answer.dir = list[iter];
				}
			}
		}
	}
}