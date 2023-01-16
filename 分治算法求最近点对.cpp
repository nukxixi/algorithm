#include<iostream>
#include<algorithm>
#include<math.h>
#include<iomanip>
using namespace std;
#define NO_DISTANCE 1000000
struct Point {
	double x, y;
};

double getDistance(Point a, Point b) {//求两点间距离
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool cmpx(Point a, Point b) {//按照横坐标排序
	return a.x < b.x;
}

double closestPair(Point* points, int length, Point& a, Point& b) {
	double distance;//记录最近距离
	double d1, d2;//两侧各自最小点对距离
	Point a1, a2, b1, b2;//保存分割后两个子集中最小点对

	if (length < 2)return NO_DISTANCE;
	else if (length == 2) {
		distance = getDistance(points[0], points[1]);

	}
	else {
		Point* pt1 = new Point[length];
		Point* pt2 = new Point[length];
		sort(points, points + length, cmpx);//按照横坐标排序
		double mid = points[(length - 1) / 2].x;//横坐标中位数
		for (int i = 0; i < length / 2; i++) {
			pt1[i] = points[i];
		}
		for (int j = 0, i = length / 2; i < length; i++) {
			pt2[j++] = points[i];
		}
		d1 = closestPair(pt1, length / 2, a1, b1);
		d2 = closestPair(pt2, length - length / 2, a2, b2);

		if (d1 < d2) {
			distance = d1;
			a = a1;
			b = b1;
		}
		else {
			distance = d2;
			a = a2;
			b = b2;
		}

		Point* pt3 = new Point[length];
		int m = 0;
		for (int i = 0; i < length; i++) {
			if (abs(points[i].x - mid) <= distance)pt3[m++] = points[i];
		}
		for (int i = 0; i < m; i++) {
			for (int j = i + 1; j < i + 750 && j < m; j++) {  //
				if (getDistance(pt3[i], pt3[j]) < distance) {
					distance = getDistance(pt3[i], pt3[j]);
					a = pt3[i];
					b = pt3[j];
				}
			}
		}
	}
	return distance;
}

int main() {
	int n;
	cin >> n;
	Point a, b;
	double distance;
	Point* points = new Point[n];
	for (int i = 0; i < n; i++) {
		cin >> points[i].x >> points[i].y;
	}
	distance = closestPair(points, n, a, b);
	cout << fixed << setprecision(2) << distance * distance;
}