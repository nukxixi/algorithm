#include<iostream>
using namespace std;

bool allMenHavePair(bool* manHasPair, int n) {//是否所有的男方都有舞伴
	for (int i = 0; i < n; i++) {
		if (!manHasPair[i])return false;
	}
	return true;
}

int findMostLike(int** Man, bool* womanHasPair, int n, int index, bool** invited) {//寻找未邀请过的女方里最偏爱的一位
	for (int i = 0; i < n; i++) {
		int w = Man[index][i];
		if (!invited[index][w])return w;
	}
	return -1;
}

int main() {
	int n;
	cin >> n;
	int** Man = new int* [n];
	for (int i = 0; i < n; i++) {
		Man[i] = new int[n];
	}
	int** Woman = new int* [n];
	for (int i = 0; i < n; i++) {
		Woman[i] = new int[n];
	}

	for (int i = 0; i < n; i++) {//男方按照偏爱程度排序  0~4号女士
		for (int j = 0; j < n; j++) {
			int h;
			cin >> h;
			Man[i][j] = h - 1;
		}
	}
	for (int i = 0; i < n; i++) {//女方按照序号排列   0~4号男士各自对应0~4号偏爱程度
		for (int j = 0; j < n; j++) {
			int x;
			cin >> x;
			Woman[i][x - 1] = j;
		}
	}

	//每一位男士邀请过的女士
	bool** invited = new bool* [n];
	for (int i = 0; i < n; i++) {
		invited[i] = new bool[n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			invited[i][j] = false;
		}
	}

	//男方或女方是否有舞伴
	bool* manHasPair = new bool[n];
	bool* womanHasPair = new bool[n];
	for (int i = 0; i < n; i++) {
		manHasPair[i] = false;
		womanHasPair[i] = false;
	}

	//已经结成舞伴
	int* pairs = new int[n];
	for (int i = 0; i < n; i++) {
		pairs[i] = -1;
	}


	int index = 0;
	while (!allMenHavePair(manHasPair, n) && index <= n - 1) {//GS算法
		int w = findMostLike(Man, womanHasPair, n, index, invited);
		invited[index][w] = true;
		if (!womanHasPair[w]) {
			pairs[w] = index;
			womanHasPair[w] = true;
			manHasPair[index] = true;
			while (manHasPair[index] && index <= n - 2) {
				index++;
			}
		}
		else {
			int k = pairs[w];
			if (Woman[w][k] < Woman[w][index])continue;
			else {
				pairs[w] = index;
				manHasPair[index] = true;
				manHasPair[k] = false;
				index = k;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j =0; j <n; j++) {
			if (pairs[j] == i)cout << j+1 ;
		}if (i != n - 1)cout << " ";
	}
	return 0;
}