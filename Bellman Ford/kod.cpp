#include <bits/stdc++.h>
using namespace std;
const int INF = numeric_limits<int>::max();
struct Edge {
    int u, v, w;
};
// Функција за Белман-Форд
bool bellmanFord(int n, int start, const vector<Edge>& edges, vector<int>& dist) {
    dist.assign(n, INF);
    dist[start] = 0;
    // Опуштање на сите ребра n-1 пати
    for (int i = 1; i < n; i++) {
        for (auto& e : edges) {
            if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.w;
            }
        }
    }
    // Проверка за негативни циклуси
    for (auto& e : edges) {
        if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
            return false; // постои негативен циклус
        }
    }
    return true;
}
int main() {
    int n, m;
    cout << "Vnesi broj na teminja i broj na rebra: ";
    cin >> n >> m;
    vector<Edge> edges(m);
    cout << "Vnesi gi rebrata (u v w):" << endl;
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    int start;
    cout << "Poceten chvor: ";
    cin >> start;
    vector<int> dist;
    if (bellmanFord(n, start, edges, dist)) {
        cout << "Najkratki rastojanija od chvorot " << start << ":" << endl;
        for (int i = 0; i < n; i++) {
            if (dist[i] == INF)
                cout << i << ": INF" << endl;
            else
                cout << i << ": " << dist[i] << endl;
        }
    } else {
        cout << "Grafot sodrzi NEGATIVEN ciklus!" << endl;
    }
    return 0;
}
