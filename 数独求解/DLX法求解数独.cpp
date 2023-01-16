#include<iostream>//dancing link求解数独
#include<vector>
#include<set>
using namespace std;

int recursion_count = 0;//递归次数
const int col_count = 9 * 9 * 4 + 1; //列数
const int row_count = 9 * 9 * 9 + 1; //行数
const int max_node = 9 * 9 * 9 * 4 + 1; //最大结点数

class dancing_links {

	int node_count;//节点数
	int cnt[col_count];//每列中的节点数
	int row[max_node], col[max_node];//节点的行索引和列索引
	int r[max_node], l[max_node], u[max_node], d[max_node];//十字链表
	int answer[row_count];//存放解的数组
	int answer_depth;//递归深度

public:
	void init();
	void remove(int c);
	void resume(int c);
	int select();
	void add(int row_idx, vector<int>& v);
	bool dfs(int depth);
	bool solve(vector<int>& v);
	void fill(vector<int>& v, int(&sudo)[9][9]);
};
void dancing_links::init() {//初始化列首元素
	for (int i = 0; i < col_count; i++) {
		l[i] = i - 1;
		r[i] = i + 1;
		u[i] = i;
		d[i] = i;
	}
	l[0] = col_count - 1;
	r[col_count - 1] = 0;

	node_count = col_count - 1 + 1;//将当前节点数置为列首元素个数+1
	for (int i = 0; i < col_count; i++) {//每列元素个数置为0
		cnt[i] = 0;
	}
}

void dancing_links::remove(int c) {//十字删除
	l[r[c]] = l[c];
	r[l[c]] = r[c];
	for (int i = d[c]; i != c; i = d[i]) {
		for (int j = r[i]; j != i; j = r[j]) {
			u[d[j]] = u[j];
			d[u[j]] = d[j];
			cnt[col[j]]--;
		}
	}
}

void dancing_links::resume(int c) {//恢复
	for (int i = u[c]; i != c; i = u[i])
	{
		for (int j = l[i]; j != i; j = l[j])
		{
			u[d[j]] = j;
			d[u[j]] = j;
			cnt[col[j]]++;
		}
	}
	l[r[c]] = c;
	r[l[c]] = c;
}
int dancing_links::select() {//选出列元素数最小的以减少递归次数
	int col_idx = r[0];
	for (int i = r[0]; i != 0; i = r[i]) {
		if (cnt[i] < cnt[col_idx])col_idx = i;
	}
	return col_idx;
}


void dancing_links::add(int row_idx, vector<int>& v) {
	for (int i = 0; i < v.size(); i++) {
		d[node_count] = v[i];
		u[node_count] = u[v[i]];
		d[u[v[i]]] = node_count;
		u[v[i]] = node_count;
		row[node_count] = row_idx;
		col[node_count] = v[i];

		cnt[v[i]]++;
		node_count++;
	}
	for (int i = 1; i <= v.size(); i++) {
		l[node_count - i] = node_count - i - 1;
		r[node_count - i] = node_count - i + 1;
	}
	r[node_count - 1] = node_count - 4;
	l[node_count - 4] = node_count - 1;
}


bool dancing_links::dfs(int depth) {
	recursion_count++;
	if (r[0] == 0) {
		answer_depth = depth;//解的长度
		return true;
	}
	int c = select();
	remove(c);
	for (int i = d[c]; i != c; i = d[i])
	{
		answer[depth] = row[i];//存入答案 由于depth与递归深度有关，递归失败则会自动覆写

		for (int j = r[i]; j != i; j = r[j])
			remove(col[j]);

		if (dfs(depth + 1))//求解成功
			return true;
		for (int j = l[i]; j != i; j = l[j])
			resume(col[j]);  //求解失败，恢复
	}
	resume(c);
	return false;

}
void dancing_links::fill(vector<int>& v, int(&sudo)[9][9]) {
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
			for (int value = 1; value <= 9; value++) {
				if (sudo[row][col] == value || sudo[row][col] == 0) {
					v.clear();
					v.push_back((row) * 9 + col + 1);//前81列——每个格子中放置与否
					v.push_back((row) * 9 + value + 81);//82-162列——每行放置9个数
					v.push_back((col) * 9 + value + 162);//163-243列——每列中放置9个数
					v.push_back((row) / 3 * 3 * 9 + (col) / 3 * 9 + 243 + value);//244-324列——每个小格中放置9个数
					add(((row) * 9 + col) * 9 + value, v);
				}
			}
		}
	}
}


bool dancing_links::solve(vector<int>& result) {
	dfs(0);
	for (int i = 0; i < answer_depth; i++) {
		result.push_back(answer[i]);
	}
	return true;
}

bool legal(int(&sudo)[9][9]) {
	vector<int>v;
	set<int>a;
	int m = 0;
	for (int i = 0; i < 9; i++) {
		m = 0;
		for (int j = 0; j < 9; j++) {
			if (sudo[i][j]) {
				a.insert(sudo[i][j]);
				m++;
			}
		}
		if (a.size() != m)return false;
		a.clear();
	}

	for (int i = 0; i < 9; i++) {
		m = 0;
		for (int j = 0; j < 9; j++) {
			if (sudo[j][i]) {
				a.insert(sudo[j][i]);
				m++;
			}
		}
		if (a.size() != m)return false;
		a.clear();
	}

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			v.push_back(sudo[i][j]);
		}
	}

	for (int i = 0; i < 9; i += 3) {
		for (int j = 0; j < 9; j += 3) {
			m = 0;
			for (int k = 0; k < 3; k++) {
				if (sudo[j + k][i] != 0) {
					a.insert(sudo[j + k][i]);
					m++;
				}
				if (sudo[j + k][i + 1] != 0) {
					a.insert(sudo[j + k][i + 1]);
					m++;
				}
				if (sudo[j + k][i + 2] != 0) {
					a.insert(sudo[j + k][i + 2]);
					m++;
				}
			}
			if (a.size() != m)return false;
			a.clear();
		}
	}
	return true;
}


int main() {
	int sudo[9][9];
	vector<int> v;
	vector<int>result;
	dancing_links d;

	while (1) {
		cout << "请输入数独（空位用0填充）：" << endl;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				cin >> sudo[i][j];
			}
		}
		cout << endl;
		if (legal(sudo))break;
		if (!legal(sudo))cout << "输入的数独不合法，请重新输入！" << endl;
	}
	
	d.init();//初始化
	d.fill(v, sudo);//填充dlx
	d.solve(result);//求解精确覆盖

	int row, col, value;
	for (int i = 0; i < result.size(); i++) {
		value = --result[i] % 9;
		result[i] /= 9;
		col = result[i] % 9;
		result[i] /= 9;
		row = result[i];
		sudo[row][col] = 1 + value;
	}

	cout << "结果为：" << endl;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
			cout << sudo[i][j] << " ";
		cout << endl;
	}
	cout << "递归次数为：" << recursion_count << endl;
	return 0;
}


