#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include<vector>

#define GRIDSIZE 15
#define judge_black 0
#define judge_white 1
#define grid_blank 0
#define grid_black 1
#define grid_white -1

int curNum = 2;//当前可以下的棋子数量

using namespace std;

int currBotColor; // 本方所执子颜色（1为黑，-1为白，棋盘状态亦同）
int gridInfo[GRIDSIZE][GRIDSIZE] = { 0 }; // 先x后y，记录棋盘状态
int dx[] = { -1,-1,-1,0,0,1,1,1 };
int dy[] = { -1,0,1,-1,1,-1,0,1 };
/*******************************************/
/********下面为使用的函数*************/
//四个方向计数返回六元组中两种颜色棋子的数目
vector<int> Count1(int x, int y);
vector<int> Count2(int x, int y);
vector<int> Count3(int x, int y);
vector<int> Count4(int x, int y);
//得到一个六元组的得分（需要优化）
int Score(vector<int> count);
//获得该点在所有方向上六元组得分总和
int GetAllScore(int x, int y);
bool IsWin();
/****************************************/



// 判断是否在棋盘内
inline bool inMap(int x, int y)
{
	if (x < 0 || x >= GRIDSIZE || y < 0 || y >= GRIDSIZE)
		return false;
	return true;
}


// 在坐标处落子，检查是否合法或模拟落子
bool ProcStep(int x0, int y0, int x1, int y1, int grid_color, bool check_only)
{
	if (x1 == -1 || y1 == -1) {
		if (!inMap(x0, y0) || gridInfo[x0][y0] != grid_blank)
			return false;
		if (!check_only) {
			gridInfo[x0][y0] = grid_color;
		}
		return true;
	}
	else {
		if ((!inMap(x0, y0)) || (!inMap(x1, y1)))
			return false;
		if (gridInfo[x0][y0] != grid_blank || gridInfo[x1][y1] != grid_blank)
			return false;
		if (!check_only) {
			gridInfo[x0][y0] = grid_color;
			gridInfo[x1][y1] = grid_color;
		}
		return true;
	}
}

vector<int> Count1(int x, int y) {//向左计数
	int black = 0, white = 0, cnt = 6;
	while (cnt > 0 && inMap(x, y)) {
		if (gridInfo[x][y] == grid_black) {
			black++;
		}
		if (gridInfo[x][y] == grid_white) {
			white++;
		}
		x--;
		cnt--;
	}
	if (cnt > 0) return {};//未构成一个六元组，返回空向量
	return vector<int>({black, white});
}
vector<int> Count2(int x, int y) {//向上计数
	int black = 0, white = 0, cnt = 6;
	while (cnt > 0 && inMap(x, y)) {
		if (gridInfo[x][y] == grid_black) {
			black++;
		}
		if (gridInfo[x][y] == grid_white) {
			white++;
		}
		y--;
		cnt--;
	}
	if (cnt > 0) return {};//未构成一个六元组，返回空向量
	return vector<int>({ black, white });
}
vector<int> Count3(int x, int y) {//向左上计数
	int black = 0, white = 0, cnt = 6;
	while (cnt > 0 && inMap(x, y)) {
		if (gridInfo[x][y] == grid_black) {
			black++;
		}
		if (gridInfo[x][y] == grid_white) {
			white++;
		}
		x--;
		y--;
		cnt--;
	}
	if (cnt > 0) return {};//未构成一个六元组，返回空向量
	return vector<int>({ black, white });
}
vector<int> Count4(int x, int y) {//向右上计数
	int black = 0, white = 0, cnt = 6;
	while (cnt > 0 && inMap(x, y)) {
		if (gridInfo[x][y] == grid_black) {
			black++;
		}
		if (gridInfo[x][y] == grid_white) {
			white++;
		}
		x++;
		y--;
		cnt--;
	}
	if (cnt > 0) return {};//未构成一个六元组，返回空向量
	return vector<int>({ black, white });
}
//得到一个六元组的得分（需要优化）
int Score(vector<int> count) {
	if (count.empty()) return 0;
	//our_side为我方棋子数目，other_side为对方棋子数目
	int our_side, other_side;
	if (currBotColor == grid_black) {
		our_side = count[0];
		other_side = count[1];
	}
	else {
		our_side = count[1];
		other_side = count[0];
	}
	if (curNum == 2) {
		if (our_side == 0) {
			switch (other_side) {
			case 0:return 1; break;
			case 1:return 10; break;
			case 2:return 100; break;
			case 3:return 1000; break;
			case 4:return 10000; break;
			case 5:return 100000; break;
			}
		}
		else if (other_side == 0) {
			switch (our_side) {
			case 1:return 35; break;
			case 2:return 350; break;
			case 3:return 3500; break;
			case 4:return 35000; break;
			case 5:return 350000; break;
			}
		}
	}
	else if (curNum == 1) {
		if (our_side == 0) {
			switch (other_side) {
			case 0:return 1; break;
			case 1:return 10; break;
			case 2:return 100; break;
			case 3:return 1000; break;
			case 4:return 35000; break;
			case 5:return 100000; break;
			}
		}
		else if (other_side == 0) {
			switch (our_side) {
			case 1:return 35; break;
			case 2:return 350; break;
			case 3:return 3500; break;
			case 4:return 10000; break;
			case 5:return 350000; break;
			}
		}
	}
	else if (our_side != 0 && other_side != 0) return 0;
	return 0;
}
//获得该点在所有方向上六元组得分总和
int GetAllScore(int x, int y) {
	int res = 0;
	//遍历六元组的起始位置
	int mx[4] = { x,x,x,x };
	int my[4] = { y,y,y,y };
	//遍历包括该点的所有六元组
	for (int i = 0; i < 6; i++) {
		if (inMap(mx[0], my[0])) {
			res += Score(Count1(mx[0], my[0]));
			mx[0]++;//往左遍历六元组，起始位置往右移
		}
		if (inMap(mx[1], my[1])) {
			res += Score(Count2(mx[1], my[1]));
			my[1]++;//往上遍历六元组，起始位置往下移
		}
		if (inMap(mx[2], my[2])) {
			res += Score(Count3(mx[2], my[2]));
			mx[2]++;
			my[2]++;//往左上遍历六元组，起始位置往右下移
		}
		if (inMap(mx[3], my[3])) {
			res += Score(Count4(mx[3], my[3]));
			mx[3]--;
			my[3]++;//往右上遍历六元组，起始位置往左下移
		}
	}
	return res;
}

bool IsWin() {//判断是否胜利
	bool flag = false;
	int k;
	if (currBotColor == grid_black) k = 0;
	else k = 1;
	for (int i = 0; i < GRIDSIZE; i++) {
		for (int j = 0; j < GRIDSIZE; j++) {
			if ((!Count1(i, j).empty() && Count1(i, j)[k] == 6 )|| (!Count2(i, j).empty() && Count2(i, j)[k] == 6) ||
				(!Count3(i, j).empty() && Count3(i, j)[k] == 6) || (!Count4(i, j).empty() && Count4(i, j)[k] == 6)) {
				flag = true;
			}
		}
	}
	return flag;
	
}

int main()
{
	int x0, y0, x1, y1;

	// 分析自己收到的输入和自己过往的输出，并恢复棋盘状态
	int turnID;
	cin >> turnID;
	currBotColor = grid_white; // 先假设自己是白方
	for (int i = 0; i < turnID; i++)
	{
		// 根据这些输入输出逐渐恢复状态到当前回合
		cin >> x0 >> y0 >> x1 >> y1;
		if (x0 == -1)
			currBotColor = grid_black; // 第一回合收到坐标是-1, -1，说明我是黑方
		if (x0 >= 0)
			ProcStep(x0, y0, x1, y1, -currBotColor, false); // 模拟对方落子
		if (i < turnID - 1) {
			cin >> x0 >> y0 >> x1 >> y1;
			if (x0 >= 0)
				ProcStep(x0, y0, x1, y1, currBotColor, false); // 模拟己方落子
		}
	}


	//决策部分
	int startX=-1, startY=-1, resultX = -1, resultY = -1;
	if (turnID == 1 && currBotColor == grid_black) {
		startX = startY = 7;
		resultX = resultY = -1;
	}
	else {

		int searchCount = 0;//遍历次数
		//遍历
		while (searchCount < 2) {
			int score, maxscore = -1, maxx = -1, maxy = -1;
			for (int i = 0; i < GRIDSIZE; i++) {
				for (int j = 0; j < GRIDSIZE; j++) {
					if (gridInfo[i][j] == grid_blank) {//确定为空位置，然后再遍历六元组
						score = GetAllScore(i, j);//获得该点的分数
						if (score > maxscore) {//寻找分数最大的点
							maxscore = score;
							maxx = i;
							maxy = j;
						}
					}
				}
			}
			searchCount++;
			curNum--;
			if (searchCount == 1) {
				startX = maxx;
				startY = maxy;
				gridInfo[startX][startY] = currBotColor;
				if (IsWin()) {
					resultX = -1;
					resultY = -1;
					searchCount++;
				}
			}
			if (searchCount == 2) {
				resultX = maxx;
				resultY = maxy;
				searchCount++;
			}
		}//end while
	}//else
	// 决策结束，向平台输出决策结果

	cout << startX << ' ' << startY << ' ' << resultX << ' ' << resultY << endl;
	return 0;
}