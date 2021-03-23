#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void showPath(const vector<int>& v, const int& idx)
{
    int p = idx;

    while (true) {
        cout << v[p];
        if (p - 1 >= 0) {
            p = (p - 1) / 2;
            cout << " ";
        } else {
            cout << "\n";
            break;
        }
    }
}

bool cmp(const int& a, const int& b)
{
    return a > b;
}

int main()
{
    int idx, N, M;
    cin >> N >> M;
    vector<int> v(N);
    for (int i = 0; i < N; i++) {
        cin >> v[i];
        push_heap(v.begin(), v.begin() + i + 1, cmp);
    }

    for (int k = 0; k < M; k++) {
        cin >> idx;
        showPath(v, idx-1);
    }

    return 0;
}