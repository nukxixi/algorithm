#include<iostream>
#include<math.h>
using namespace std;
const int N = 2002;
int main() {
	string a, b;
	int k;
	cin >> a >> b >> k;
	int len1 = a.length();
	int len2 = b.length();

	int f[2][N];

	for (int j = 0; j <= len2; j++) {
		f[0][j] = k * j;
	}

	for (int i = 1; i <= len1; i++) {
		f[1][0] = i * k;
		for (int j = 1; j <= len2; j++) {
			f[1][j] = min(min(f[1][j - 1], f[0][j]) + k, f[0][j - 1] + abs(a[i - 1] - b[j - 1]));
		}

		for (int j = 0; j <= len2; j++) {
			f[0][j] = f[1][j];
		}
	}
	cout << f[0][len2];

}