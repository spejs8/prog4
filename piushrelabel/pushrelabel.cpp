#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void push(int u, int v, vector<vector <int> > &flow, vector<int> &excess, queue<int> &excess_vertices, vector<vector<int> >&capacity) {
    int d = min(excess[u], capacity[u][v] - flow[u][v]);
    flow[u][v] += d;
    flow[v][u] -= d;
    excess[u] -= d;
    excess[v] += d;
    if (d>0 && excess[v]==d) { excess_vertices.push(v); }
}

void relabel(int u, int n,vector<vector<int>> &flow,vector<vector<int> > &capacity , vector<int> &height) {
    int d=10000000;
    for (int i = 0; i < n; i++) {
        if (capacity[u][i]-flow[u][i]>0) { d=min(d, height[i]); }
    }
    if (d!=10000000) { height[u]=d+1; }
}
void discharge(int u, int n, vector<int> &seen,vector<vector<int> > &flow,vector<vector<int> > &capacity , vector<int> &height, vector<int> &excess, queue<int> &excess_vertices) {
    while (excess[u]>0) {
        if (seen[u]<n) {
            int v=seen[u];
            if (capacity[u][v]-flow[u][v]>0 && height[u]>height[v]) { push(u, v, flow, excess, excess_vertices, capacity); }
            else seen[u]++;
        }
        else {
            relabel(u, n, flow, capacity, height);
            seen[u]=0;
        }
    }
}

int max_flow(int s, int t, int n, vector<int> &seen, vector<vector<int> > &flow, queue<int> &excess_vertices , vector<int> &height, vector<int> &excess, vector<vector<int>> &capacity) {
    for (int i=1; i<n; i++) {
        push(s, i, flow, excess, excess_vertices, capacity);
    }
    while (excess_vertices.size()!=0) {
        int u=excess_vertices.front();
        excess_vertices.pop();
        if (u!=s && u!=t) {  discharge(u, n, seen, flow, capacity, height, excess, excess_vertices); }
    }
    int max_flow=0;
    for (int i=0; i<n; i++) {
        max_flow+=flow[i][t];
    }
    return max_flow;
}

int main () {
    int n,m;
    cin>>n>>m;
    vector<vector<int>> capacity(n,vector<int>(n, 0));
    vector<vector<int>> flow(n,vector<int>(n, 0));
    vector<int> height(n,0), excess(n,0), seen(n,0);
    queue<int> excess_vertices;
    height[0]=n;
    excess[0]=10000000;
    for (int i=0; i<m; i++) {
        int tmp, tmp1, tmp2;
        cin>>tmp>>tmp1>>tmp2;
        capacity[tmp][tmp1]=tmp2;
    }
    cout<<"Max flow e "<<max_flow(0,n-1,n,seen,flow,excess_vertices, height, excess, capacity)<<endl;
}