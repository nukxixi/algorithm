#include<iostream> //回溯法求解数独
#include<set>
#include<vector>
using namespace std;

int recursion_count = 0;
bool flag = false;
int sudo[9][9];

bool judge_legal(int n, int value) { //第n个格填入value，判断是否合法
    for (int i = 0; i < 9; i++) {//判断行
        if (sudo[n / 9][i] == value)
            return false;
    }

    for (int i = 0; i < 9; i++) {//判断列
        if (sudo[i][n % 9] == value)
            return false;
    }

    //判断小九宫格
    int x = n / 9 / 3 * 3;
    int y = n % 9 / 3 * 3;
    for (int i = x; i < x + 3; i++) {
        for (int j = y; j < y + 3; j++) {
            if (sudo[i][j] == value)
                return false;
        }
    }
    return true;
}

bool dfs(int m) {
    recursion_count++;
    if (m > 80) {//递归结束
        flag = true;
        return true;
    }
    if (sudo[m / 9][m % 9] != 0) {//该位置已有数字
        dfs(m + 1);
    }
    else {
        for (int i = 1; i <= 9; i++) {
            if (judge_legal(m, i)) {
                sudo[m / 9][m % 9] = i;
                
                dfs(m + 1);
                
                if (flag == true) {
                    return true;
                }
                sudo[m / 9][m % 9] = 0; //还原
            }
        }
    }
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

    dfs(0);
    cout << "结果为：" << endl;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << sudo[i][j] << " ";
        }cout << endl;
    }

    cout << "递归次数为：" << recursion_count;
    return 0;
}
