#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int CL(const string& s, int L) {
    int n = s.size();
    if (L == 0) return -1;
    const unsigned long long baza = 131;
    unsigned long long h = 0;
    for (int i = 0; i < L; i++) h = h * baza + (s[i] - 'a' + 1);
    vector<pair<unsigned long long,int>> lista;
    lista.push_back({h,0});
    unsigned long long p = 1;
    for (int i = 1; i < L; i++) p *= baza;
    for (int start = 1; start + L <= n; start++) {
        unsigned long long levo = (s[start - 1] - 'a' + 1);
        unsigned long long desno = (s[start + L - 1] - 'a' + 1);
        h = h - levo * p;
        h = h * baza + desno;
        lista.push_back({h,start});
    }
    sort(lista.begin(), lista.end());
    for (int i = 1; i < (int)lista.size(); i++) {
        if (lista[i].first == lista[i - 1].first) {
            int a = lista[i].second;
            int b = lista[i - 1].second;
            if (s.compare(a, L, s, b, L) == 0) return a;
        }
    }
    return -1;
}

string longestDupSubstring(string s) {
    int n = s.size();
    int lo = 1, hi = n - 1;
    int bestLen = 0, bestStart = -1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        int pos = CL(s, mid);
        if (pos != -1) {
            bestLen = mid;
            bestStart = pos;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    if (bestStart == -1) return "";
    return s.substr(bestStart, bestLen);
}

int main() {
    string s;
    cin >> s;
    cout << longestDupSubstring(s) << "\n";
    return 0;
}