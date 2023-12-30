#include <bits/stdc++.h>
using namespace std;

bool dfs(vector<int>& L, vector<int>& R, int boat) {
    if (R.size() == 3) {
        return true;
    }
    for (int i = 0; i < L.size(); i++) {
        for (int j = i + 1; j < L.size(); j++) {
            if (L[i] + L[j] <= 100) {
                vector<int> newL = L;
                vector<int> newR = R;
                newL.erase(newL.begin() + j);
                newL.erase(newL.begin() + i);
                newR.push_back(L[i]);
                newR.push_back(L[j]);
                if (dfs(newL, newR, 1 - boat)) {
                    cout << "Move " << L[i] << " and " << L[j] << " from left to right" << endl;
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    vector<int> L = {100, 50, 50};
    vector<int> R = {};
    dfs(L, R, 0);
    return 0;
}