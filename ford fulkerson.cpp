#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class pat {
public:
    int pocetno;
    int krajno;
    int tezina;
};

int dfs (int i, int v, vector<vector<int> > &graf, vector<int> &poseteni , vector<pat> &pateka , int minflow=10000000) {
    if (i==v-1) { return minflow; }
    poseteni[i]=1;
    for (int k=0; k<v; k++) {
        if (poseteni[k]==0 && graf[i][k]!=0) { 
            int vrednost=dfs(k, v, graf, poseteni,pateka, min(minflow,graf[i][k]));
            if (vrednost!=0) {
                //cout<<i<<"->"<<k<<"("<<graf[i][k]<<")"<<",";
                pateka.push_back({i,k,graf[i][k]});
                graf[i][k]-=vrednost;
                graf[k][i]+=vrednost;
                return vrednost;
            }
        }
    }
    return 0;
}

int main () {
    int e,v,flow=0;
    cin>>v>>e;
    vector<vector<int> > graf(v,vector<int>(v,0));
    for (int i=0; i<e; i++) {
        int tmp,tmp1,tmp2;
        cin>>tmp>>tmp1>>tmp2;
        graf[tmp][tmp1]=tmp2;
    }
    while (1) {
        vector<int> a(v,0);
        vector<pat> b;
        int p=dfs (0,v,graf,a,b);
        if (p==0) { break; }
        while (b.size()!=0) {
            pat tmp=b.back();
            b.pop_back();
            cout<<tmp.pocetno<<"->"<<tmp.krajno<<"("<<tmp.tezina<<"), ";
        }
        cout<<endl;
        flow+=p;
    }
    cout<<flow;
}