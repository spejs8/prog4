#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

unsigned long long myhash(const string &a) {
    const unsigned long long baza = 131;
    unsigned long long h = 0;
    for (char c : a) {
        h = h * baza + (c - 'a' + 1);
    }
    return h;
}

int main() {
    string s;
    cin >> s;
    int n = s.size();

    vector<int> rezultat(n + 1, 0);
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {

            string t = s.substr(i, j - i + 1);
            string r = t;
            reverse(r.begin(), r.end());

            if (myhash(t) == myhash(r)) dp[i][j] = 1;
            else continue;

            int len = j - i + 1;

            if (len >= 2) {
                int mid = len / 2;
                string left = t.substr(0, mid);
                string right = t.substr(len - mid, mid);

                if (myhash(left) == myhash(right)) {
                    if (dp[i][i + mid - 1] >= 1 && dp[j - mid + 1][j] >= 1) {
                        dp[i][j] = 2;
                    }
                }
            }

            rezultat[dp[i][j]]++;
        }
    }

    for (int k = 1; k <= n; k++) {
        if (k > 1) cout << " ";
        cout << rezultat[k];
    }
    cout << endl;

    return 0;
}