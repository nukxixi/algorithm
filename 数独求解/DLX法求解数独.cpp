#include<iostream>//dancing link�������
#include<vector>
#include<set>
using namespace std;

int recursion_count = 0;//�ݹ����
const int col_count = 9 * 9 * 4 + 1; //����
const int row_count = 9 * 9 * 9 + 1; //����
const int max_node = 9 * 9 * 9 * 4 + 1; //�������

class dancing_links {

	int node_count;//�ڵ���
	int cnt[col_count];//ÿ���еĽڵ���
	int row[max_node], col[max_node];//�ڵ����������������
	int r[max_node], l[max_node], u[max_node], d[max_node];//ʮ������
	int answer[row_count];//��Ž������
	int answer_depth;//�ݹ����

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
void dancing_links::init() {//��ʼ������Ԫ��
	for (int i = 0; i < col_count; i++) {
		l[i] = i - 1;
		r[i] = i + 1;
		u[i] = i;
		d[i] = i;
	}
	l[0] = col_count - 1;
	r[col_count - 1] = 0;

	node_count = col_count - 1 + 1;//����ǰ�ڵ�����Ϊ����Ԫ�ظ���+1
	for (int i = 0; i < col_count; i++) {//ÿ��Ԫ�ظ�����Ϊ0
		cnt[i] = 0;
	}
}

void dancing_links::remove(int c) {//ʮ��ɾ��
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

void dancing_links::resume(int c) {//�ָ�
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
int dancing_links::select() {//ѡ����Ԫ������С���Լ��ٵݹ����
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
		answer_depth = depth;//��ĳ���
		return true;
	}
	int c = select();
	remove(c);
	for (int i = d[c]; i != c; i = d[i])
	{
		answer[depth] = row[i];//����� ����depth��ݹ�����йأ��ݹ�ʧ������Զ���д

		for (int j = r[i]; j != i; j = r[j])
			remove(col[j]);

		if (dfs(depth + 1))//���ɹ�
			return true;
		for (int j = l[i]; j != i; j = l[j])
			resume(col[j]);  //���ʧ�ܣ��ָ�
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
					v.push_back((row) * 9 + col + 1);//ǰ81�С���ÿ�������з������
					v.push_back((row) * 9 + value + 81);//82-162�С���ÿ�з���9����
					v.push_back((col) * 9 + value + 162);//163-243�С���ÿ���з���9����
					v.push_back((row) / 3 * 3 * 9 + (col) / 3 * 9 + 243 + value);//244-324�С���ÿ��С���з���9����
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
		cout << "��������������λ��0��䣩��" << endl;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				cin >> sudo[i][j];
			}
		}
		cout << endl;
		if (legal(sudo))break;
		if (!legal(sudo))cout << "������������Ϸ������������룡" << endl;
	}
	
	d.init();//��ʼ��
	d.fill(v, sudo);//���dlx
	d.solve(result);//��⾫ȷ����

	int row, col, value;
	for (int i = 0; i < result.size(); i++) {
		value = --result[i] % 9;
		result[i] /= 9;
		col = result[i] % 9;
		result[i] /= 9;
		row = result[i];
		sudo[row][col] = 1 + value;
	}

	cout << "���Ϊ��" << endl;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
			cout << sudo[i][j] << " ";
		cout << endl;
	}
	cout << "�ݹ����Ϊ��" << recursion_count << endl;
	return 0;
}


