#include<iostream>
using namespace std;

bool allMenHavePair(bool* manHasPair, int n) {//�Ƿ����е��з��������
	for (int i = 0; i < n; i++) {
		if (!manHasPair[i])return false;
	}
	return true;
}

int findMostLike(int** Man, bool* womanHasPair, int n, int index, bool** invited) {//Ѱ��δ�������Ů������ƫ����һλ
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

	for (int i = 0; i < n; i++) {//�з�����ƫ���̶�����  0~4��Ůʿ
		for (int j = 0; j < n; j++) {
			int h;
			cin >> h;
			Man[i][j] = h - 1;
		}
	}
	for (int i = 0; i < n; i++) {//Ů�������������   0~4����ʿ���Զ�Ӧ0~4��ƫ���̶�
		for (int j = 0; j < n; j++) {
			int x;
			cin >> x;
			Woman[i][x - 1] = j;
		}
	}

	//ÿһλ��ʿ�������Ůʿ
	bool** invited = new bool* [n];
	for (int i = 0; i < n; i++) {
		invited[i] = new bool[n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			invited[i][j] = false;
		}
	}

	//�з���Ů���Ƿ������
	bool* manHasPair = new bool[n];
	bool* womanHasPair = new bool[n];
	for (int i = 0; i < n; i++) {
		manHasPair[i] = false;
		womanHasPair[i] = false;
	}

	//�Ѿ�������
	int* pairs = new int[n];
	for (int i = 0; i < n; i++) {
		pairs[i] = -1;
	}


	int index = 0;
	while (!allMenHavePair(manHasPair, n) && index <= n - 1) {//GS�㷨
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