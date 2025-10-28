#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int dfs (int i, int v, vector<vector<int> > &graf, vector<int> &poseteni , int minflow=10000000) {
    if (i==v-1) { return minflow; }
    poseteni[i]=1;
    for (int k=0; k<v; k++) {
        if (poseteni[k]==0 && graf[i][k]!=0) { 
            int vrednost=dfs(k, v, graf, poseteni, min(minflow,graf[i][k]));
            if (vrednost!=0) {
                //cout<<i<<"->"<<k<<"("<<graf[i][k]<<")"<<",";
                graf[i][k]-=vrednost;
                graf[k][i]+=vrednost;
                return vrednost;
            }
        }
    }
    return 0;
}

int ford_fulkerson (vector<vector<int> > graf) {
    int flow=0;
    while (1) {
        vector<int> poseteni(graf.size(),0);
        int p=dfs(0,graf.size(),graf,poseteni);
        if (p==0) { break; }
        flow+=p;
    }
    return flow;
}

int main () {
    int e,v,minflow;
    cin>>v>>e;
    vector<vector<int> > graf(v,vector<int>(v,0));
    for (int i=0; i<e; i++) {
        int tmp,tmp1,tmp2;
        cin>>tmp>>tmp1>>tmp2;
        graf[tmp][tmp1]=tmp2;
    }
    minflow=ford_fulkerson(graf);
    for (int i=0; i<v; i++) {
        for (int j=0; j<v; j++) {
            if (graf[i][j]!=0) {
                int tmp=graf[i][j];
                graf[i][j]=0;
                minflow=min(minflow,ford_fulkerson(graf));
                graf[i][j]=tmp;
            }
        }
    }
    cout<<minflow;
}