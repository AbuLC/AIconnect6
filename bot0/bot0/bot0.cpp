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

int curNum = 2;//��ǰ�����µ���������

using namespace std;

int currBotColor; // ������ִ����ɫ��1Ϊ�ڣ�-1Ϊ�ף�����״̬��ͬ��
int gridInfo[GRIDSIZE][GRIDSIZE] = { 0 }; // ��x��y����¼����״̬
int dx[] = { -1,-1,-1,0,0,1,1,1 };
int dy[] = { -1,0,1,-1,1,-1,0,1 };
/*******************************************/
/********����Ϊʹ�õĺ���*************/
//�ĸ��������������Ԫ����������ɫ���ӵ���Ŀ
vector<int> Count1(int x, int y);
vector<int> Count2(int x, int y);
vector<int> Count3(int x, int y);
vector<int> Count4(int x, int y);
//�õ�һ����Ԫ��ĵ÷֣���Ҫ�Ż���
int Score(vector<int> count);
//��øõ������з�������Ԫ��÷��ܺ�
int GetAllScore(int x, int y);
bool IsWin();
/****************************************/



// �ж��Ƿ���������
inline bool inMap(int x, int y)
{
	if (x < 0 || x >= GRIDSIZE || y < 0 || y >= GRIDSIZE)
		return false;
	return true;
}


// �����괦���ӣ�����Ƿ�Ϸ���ģ������
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

vector<int> Count1(int x, int y) {//�������
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
	if (cnt > 0) return {};//δ����һ����Ԫ�飬���ؿ�����
	return vector<int>({black, white});
}
vector<int> Count2(int x, int y) {//���ϼ���
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
	if (cnt > 0) return {};//δ����һ����Ԫ�飬���ؿ�����
	return vector<int>({ black, white });
}
vector<int> Count3(int x, int y) {//�����ϼ���
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
	if (cnt > 0) return {};//δ����һ����Ԫ�飬���ؿ�����
	return vector<int>({ black, white });
}
vector<int> Count4(int x, int y) {//�����ϼ���
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
	if (cnt > 0) return {};//δ����һ����Ԫ�飬���ؿ�����
	return vector<int>({ black, white });
}
//�õ�һ����Ԫ��ĵ÷֣���Ҫ�Ż���
int Score(vector<int> count) {
	if (count.empty()) return 0;
	//our_sideΪ�ҷ�������Ŀ��other_sideΪ�Է�������Ŀ
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
//��øõ������з�������Ԫ��÷��ܺ�
int GetAllScore(int x, int y) {
	int res = 0;
	//������Ԫ�����ʼλ��
	int mx[4] = { x,x,x,x };
	int my[4] = { y,y,y,y };
	//���������õ��������Ԫ��
	for (int i = 0; i < 6; i++) {
		if (inMap(mx[0], my[0])) {
			res += Score(Count1(mx[0], my[0]));
			mx[0]++;//���������Ԫ�飬��ʼλ��������
		}
		if (inMap(mx[1], my[1])) {
			res += Score(Count2(mx[1], my[1]));
			my[1]++;//���ϱ�����Ԫ�飬��ʼλ��������
		}
		if (inMap(mx[2], my[2])) {
			res += Score(Count3(mx[2], my[2]));
			mx[2]++;
			my[2]++;//�����ϱ�����Ԫ�飬��ʼλ����������
		}
		if (inMap(mx[3], my[3])) {
			res += Score(Count4(mx[3], my[3]));
			mx[3]--;
			my[3]++;//�����ϱ�����Ԫ�飬��ʼλ����������
		}
	}
	return res;
}

bool IsWin() {//�ж��Ƿ�ʤ��
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

	// �����Լ��յ���������Լ���������������ָ�����״̬
	int turnID;
	cin >> turnID;
	currBotColor = grid_white; // �ȼ����Լ��ǰ׷�
	for (int i = 0; i < turnID; i++)
	{
		// ������Щ��������𽥻ָ�״̬����ǰ�غ�
		cin >> x0 >> y0 >> x1 >> y1;
		if (x0 == -1)
			currBotColor = grid_black; // ��һ�غ��յ�������-1, -1��˵�����Ǻڷ�
		if (x0 >= 0)
			ProcStep(x0, y0, x1, y1, -currBotColor, false); // ģ��Է�����
		if (i < turnID - 1) {
			cin >> x0 >> y0 >> x1 >> y1;
			if (x0 >= 0)
				ProcStep(x0, y0, x1, y1, currBotColor, false); // ģ�⼺������
		}
	}


	//���߲���
	int startX=-1, startY=-1, resultX = -1, resultY = -1;
	if (turnID == 1 && currBotColor == grid_black) {
		startX = startY = 7;
		resultX = resultY = -1;
	}
	else {

		int searchCount = 0;//��������
		//����
		while (searchCount < 2) {
			int score, maxscore = -1, maxx = -1, maxy = -1;
			for (int i = 0; i < GRIDSIZE; i++) {
				for (int j = 0; j < GRIDSIZE; j++) {
					if (gridInfo[i][j] == grid_blank) {//ȷ��Ϊ��λ�ã�Ȼ���ٱ�����Ԫ��
						score = GetAllScore(i, j);//��øõ�ķ���
						if (score > maxscore) {//Ѱ�ҷ������ĵ�
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
	// ���߽�������ƽ̨������߽��

	cout << startX << ' ' << startY << ' ' << resultX << ' ' << resultY << endl;
	return 0;
}