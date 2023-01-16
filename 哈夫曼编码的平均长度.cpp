#include<iostream>
#include<queue>
#include<iomanip>
using namespace std;
int main() {
	int n;
	cin >> n;
	int count = 0;
	int* arr = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
		count += arr[i];
	}
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1 - i; j++) {
			if (arr[j] > arr[j + 1]) {
				int tmp;
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}
	int sum = 0;
	priority_queue<int, vector<int>, greater<int>> q0;
	for (int i = 0; i < n; i++) {
		q0.push(arr[i]);
	}
	while (q0.size() > 1) {
		int min1, min2;
		min1 = q0.top();
		q0.pop();
		min2 = q0.top();
		q0.pop();
		sum += min1 + min2;
		q0.push(min1 + min2);//最小的元素相加 push进入队列
	}
	cout.setf(ios::fixed);//控制输出两位小数
	cout << fixed << setprecision(2) << (double)sum / (double)count;
	return 0;

}