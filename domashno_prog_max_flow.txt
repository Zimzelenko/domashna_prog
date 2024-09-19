#include <bits/stdc++.h>
using namespace std;

class Graph{
protected:
    int n;//br na teminja
public:
    Graph(){
        n=0;
    }
    Graph(int n){
        this->n=n;
    }
};

class GraphAdjList : public Graph{
    vector<vector<pair<int,int>>> adjList;
 public:
    GraphAdjList(int n) : Graph(n), adjList(n){}
    void addEdge(int k, int m, int cap){
        adjList[k].push_back({m,cap});
    }
    int bfs(int s, int t, vector<int>& parent, vector<vector<int>> capacity) {
        fill(parent.begin(), parent.end(), -1);
        parent[s] = -2;
        queue<pair<int, int>> q;
        q.push({s, 10000});
    
        while (!q.empty()) {
            int c = q.front().first;
            int f = q.front().second;
            q.pop();
            //cout<<c<<" "<<f<<endl;
            for (pair<int,int> el : adjList[c]) {
                int nxt=el.first;
                //cout<<nxt<<" ";
                //cout<<capacity[c][nxt]<<endl;
                if (parent[nxt] == -1 && capacity[c][nxt]) {
                    parent[nxt] = c;
                    int nf = min(f, capacity[c][nxt]);
                    if (nxt == t)
                        return nf;
                    q.push({nxt, nf});
                }
            }
            //cout<<endl;
        }
    
        return 0;
    }
    int edmond_karp(int s=0, int t=-1) {
        vector<vector<int>> capacity(n,vector<int>(n,0));
        for(int i=0;i<n;i++){
            for(int j=0;j<adjList[i].size();j++)
            capacity[i][adjList[i][j].first]=adjList[i][j].second;
        }
        int f = 0;
        vector<int> parent(n);
        int nf;
        if(t==-1)t=n-1;
        //cout<<t<<endl;
        while (nf = bfs(s, t, parent, capacity)) {
            //cout<<f<<" ";
            f += nf;
            int c = t;
            while (c != s) {
                int pr = parent[c];
                capacity[pr][c] -= nf;
                capacity[c][pr] += nf;
                c = pr;
            }
        }
       // cout<<endl;
        return f;
    }
    int dfs(int s, int t, vector<int>& parent, vector<vector<int>> capacity) {
        fill(parent.begin(), parent.end(), -1);
        parent[s] = -2;
        stack<pair<int, int>> st;
        st.push({s, 10000});
    
        while (!st.empty()) {
            int c = st.top().first;
            int f = st.top().second;
            st.pop();
    
            for (pair<int,int> el : adjList[c]) {
                int nxt=el.first;
                if (parent[nxt] == -1 && capacity[c][nxt]) {
                    parent[nxt] = c;
                    int nf = min(f, capacity[c][nxt]);
                    if (nxt == t)
                        return nf;
                    st.push({nxt, nf});
                }
            }
        }
    
        return 0;
    }
    
    int ford_flukerson(int s=0, int t=-1) {
        vector<vector<int>> capacity(n,vector<int>(n,0));
        for(int i=0;i<n;i++){
            for(int j=0;j<adjList[i].size();j++)
            capacity[i][adjList[i][j].first]=adjList[i][j].second;
        }
        int f = 0;
        vector<int> parent(n);
        int nf;
        if(t==-1)t=n-1;
        while (nf = dfs(s, t, parent, capacity)) {
            f += nf;
            int c = t;
            while (c != s) {
                int pr = parent[c];
                capacity[pr][c] -= nf;
                capacity[c][pr] += nf;
                c = pr;
            }
        }
    
        return f;
    }
};
class GraphAdjMatrix : public Graph{
    vector<vector<int>> adjMatrix;
    vector<vector<int>> adjList;
public:
    GraphAdjMatrix(int n) : Graph(n), adjMatrix(n, vector<int>(n,0)),adjList(n){}
    void addEdge(int k, int m, int cap){
        adjMatrix[k][m]=cap;
        adjList[k].push_back(m);
    }
    int bfs(int s, int t, vector<int>& parent, vector<vector<int>> capacity) {
        fill(parent.begin(), parent.end(), -1);
        parent[s] = -2;
        queue<pair<int, int>> q;
        q.push({s, 10000});
    
        while (!q.empty()) {
            int c = q.front().first;
            int f = q.front().second;
            q.pop();
            //cout<<c<<" "<<f<<endl;
            for (int nxt : adjList[c]) {
                //cout<<nxt<<" ";
                //cout<<capacity[c][nxt]<<endl;
                if (parent[nxt] == -1 && capacity[c][nxt]) {
                    parent[nxt] = c;
                    int nf = min(f, capacity[c][nxt]);
                    if (nxt == t)
                        return nf;
                    q.push({nxt, nf});
                }
            }
            //cout<<endl;
        }
    
        return 0;
    }
    int dfs(int s, int t, vector<int>& parent, vector<vector<int>> capacity) {
        fill(parent.begin(), parent.end(), -1);
        parent[s] = -2;
        stack<pair<int, int>> st;
        st.push({s, 10000});
    
        while (!st.empty()) {
            int c = st.top().first;
            int f = st.top().second;
            st.pop();
    
            for (int nxt : adjList[c]) {
                if (parent[nxt] == -1 && capacity[c][nxt]) {
                    parent[nxt] = c;
                    int nf = min(f, capacity[c][nxt]);
                    if (nxt == t)
                        return nf;
                    st.push({nxt, nf});
                }
            }
        }
    
        return 0;
    }
    int ford_flukerson(int s=0, int t=-1) {
        vector<vector<int>> capacity(adjMatrix);
        int f = 0;
        vector<int> parent(n);
        int nf;
        if(t==-1)t=n-1;
        while (nf = dfs(s, t, parent, capacity)) {
            f += nf;
            int c = t;
            while (c != s) {
                int pr = parent[c];
                capacity[pr][c] -= nf;
                capacity[c][pr] += nf;
                c = pr;
            }
        }
    
        return f;
    }
    int edmond_karp(int s=0, int t=-1) {
        vector<vector<int>> capacity(adjMatrix);
        int f = 0;
        vector<int> parent(n);
        int nf;
        if(t==-1)t=n-1;
        while (nf = bfs(s, t, parent, capacity)) {
            f += nf;
            int c = t;
            while (c != s) {
                int pr = parent[c];
                capacity[pr][c] -= nf;
                capacity[c][pr] += nf;
                c = pr;
            }
        }
    
        return f;
    }
    
};
int main()
{
    int v,e;cin>>v>>e;
    GraphAdjMatrix g(v);
    int k,m,cap;
    for(int i=0;i<e;i++){
        cin>>k>>m>>cap;
        g.addEdge(k,m,cap);
    }
    cout<<g.edmond_karp()<<" "<<g.ford_flukerson();
    return 0;
}
