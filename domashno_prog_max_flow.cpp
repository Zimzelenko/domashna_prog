#include <bits/stdc++.h>
#include <climits>
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
    vector<int> level, height, excess, seen;
    queue<int> excess_v;
 public:
    GraphAdjList(int n) : Graph(n), adjList(n), level(n), height(n,0), excess(n,0), seen(n,0){}
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
    bool dinic_bfs(int s, int t, vector<vector<int>>& capacity, vector<vector<int>>& flow) {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (pair<int, int> el : adjList[u]) {
                int v = el.first;
                if (level[v] == -1 && flow[u][v] < capacity[u][v]) {
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }
        return level[t] != -1;
    }

    int dinic_dfs(int u, int t, int flow_val, vector<vector<int>>& capacity, vector<vector<int>>& flow, vector<int>& ptr) {
        if (u == t) {
            return flow_val;
        }

        for (int& i = ptr[u]; i < adjList[u].size(); i++) {
            int v = adjList[u][i].first;
            if (level[v] == level[u] + 1 && flow[u][v] < capacity[u][v]) {
                int curr_flow = min(flow_val, capacity[u][v] - flow[u][v]);
                int temp_flow = dinic_dfs(v, t, curr_flow, capacity, flow, ptr);

                if (temp_flow > 0) {
                    flow[u][v] += temp_flow;
                    flow[v][u] -= temp_flow;
                    return temp_flow;
                }
            }
        }

        return 0;
    }

    int dinic(int s=0, int t=-1) {
        if (t == -1) t = n - 1;
        vector<vector<int>> capacity(n, vector<int>(n, 0));
        vector<vector<int>> flow(n, vector<int>(n, 0));

        for (int i = 0; i < n; i++) {
            for (pair<int, int> el : adjList[i]) {
                capacity[i][el.first] = el.second;
            }
        }

        int max_flow = 0;
        while (dinic_bfs(s, t, capacity, flow)) {
            vector<int> ptr(n, 0);
            while (int pushed_flow = dinic_dfs(s, t, INT_MAX, capacity, flow, ptr)) {
                max_flow += pushed_flow;
            }
        }

        return max_flow;
    }
    void find_min_cut(int s=0, int t=-1) {

        vector<bool> visited(n, false);
        queue<int> q;
        q.push(s);
        visited[s] = true;
        
        vector<vector<int>> capacity(n,vector<int>(n,0));
        for(int i=0;i<n;i++){
            for(int j=0;j<adjList[i].size();j++)
            capacity[i][adjList[i][j].first]=adjList[i][j].second;
        }
        vector<vector<int>> tmp(capacity);
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
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (pair<int, int> el : adjList[u]) {
                int v = el.first;
                if (!visited[v] && 0 < capacity[u][v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        cout << "Min-Cut edges: " << endl;
        for (int u = 0; u < n; u++) {
            if (visited[u]) {
                for (pair<int, int> el : adjList[u]) {
                    int v = el.first;
                    if (!visited[v] && tmp[u][v] > 0) {
                        cout << u << " - " << v << " (Capacity: " << tmp[u][v] << ")" << endl;
                    }
                }
            }
        }
    }
    void push(int s, int i, vector<vector<int>> &flow, vector<vector<int>> &capacity){
        int d = min(excess[s], capacity[s][i] - flow[s][i]);
        flow[s][i] += d;
        flow[i][s] -= d;
        excess[s] -= d;
        excess[i] += d;
        if (d && excess[i] == d)
            excess_v.push(i);
    }
    void relabel(int u, vector<vector<int>> &flow, vector<vector<int>> &capacity){
        int d=INT_MAX;
        for(int i=0;i<n;i++){
            if(capacity[u][i]-flow[u][i]>0)
                d=min(d, height[i]);
        }
        if(d<INT_MAX)
            height[u]=d+1;
    }
    void discharge(int u, vector<vector<int>> &flow, vector<vector<int>> &capacity){
        while(excess[u]>0){
            if(seen[u] < n){
                int v=seen[u];
                if(capacity[u][v]-flow[u][v]>0 && height[u]>height[v])
                    push(u,v,flow,capacity);
                else
                    seen[u]++;
            }
            else{
                relabel(u, flow, capacity);
                seen[u]=0;
            }
        }
    }
    int pushRelabel(int s=0, int t=-1){
        height[s]=n;
        excess[s]=INT_MAX;
        vector<vector<int>> flow(n,vector<int>(n,0));
        //queue<int> excess_v;
        vector<vector<int>> capacity(n,vector<int>(n,0));
        for(int i=0;i<n;i++){
            for(int j=0;j<adjList[i].size();j++)
            capacity[i][adjList[i][j].first]=adjList[i][j].second;
        }
        if(t==-1)t=n-1;
        for (int i = 0; i<n; i++) {
            if (i!=s)
                push(s, i,flow,capacity);
        }
        while(!excess_v.empty()){
            int u=excess_v.front();
            excess_v.pop();
            if(u!=s && u!=t)
                discharge(u,flow,capacity);
        }
        int max_flow=0;
        for(int i=0;i<n;i++){
            max_flow+=flow[i][t];
        }
        return max_flow;
    }
};
class GraphAdjMatrix : public Graph{
    vector<vector<int>> adjMatrix;
    vector<vector<int>> adjList;
    vector<int> level, height, excess, seen;
    queue<int> excess_v;
public:
    GraphAdjMatrix(int n) : Graph(n), adjMatrix(n, vector<int>(n,0)),adjList(n), level(n), height(n,0), excess(n,0), seen(n,0){}
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
    bool dbfs(int s, int t, vector<vector<int>>& flow) {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adjList[u]) {
                if (level[v] == -1 && flow[u][v] < adjMatrix[u][v]) {
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }
        return level[t] != -1;
    }

    int ddfs(int u, int t, int flow_val, vector<vector<int>>& flow, vector<int>& ptr) {
        if (u == t) {
            return flow_val;
        }

        for (int& i = ptr[u]; i < adjList[u].size(); i++) {
            int v = adjList[u][i];
            if (level[v] == level[u] + 1 && flow[u][v] < adjMatrix[u][v]) {
                int curr_flow = min(flow_val, adjMatrix[u][v] - flow[u][v]);
                int temp_flow = ddfs(v, t, curr_flow, flow, ptr);

                if (temp_flow > 0) {
                    flow[u][v] += temp_flow;
                    flow[v][u] -= temp_flow;
                    return temp_flow;
                }
            }
        }

        return 0;
    }
    int dinic(int s = 0, int t = -1) {
        if (t == -1) t = n - 1;
        vector<vector<int>> flow(n, vector<int>(n, 0));

        int max_flow = 0;
        while (dbfs(s, t, flow)) {
            vector<int> ptr(n, 0);
            while (int pushed_flow = ddfs(s, t, INT_MAX, flow, ptr)) {
                max_flow += pushed_flow;
            }
        }

        return max_flow;
    }
    void find_min_cut(int s = 0, int t = -1) {
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(s);
        visited[s] = true;
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
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adjList[u]) {
                if (!visited[v] && capacity[u][v] > 0) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        
        cout << "Min-Cut edges: " << endl;
        for (int u = 0; u < n; u++) {
            if (visited[u]) {
                for (int v : adjList[u]) {
                    if (!visited[v] && adjMatrix[u][v] > 0) {
                        cout << u << " - " << v << " (Capacity: " << adjMatrix[u][v] << ")" << endl;
                    }
                }
            }
        }
    }
    void push(int s, int i, vector<vector<int>> &flow){
        int d = min(excess[s], adjMatrix[s][i] - flow[s][i]);
        flow[s][i] += d;
        flow[i][s] -= d;
        excess[s] -= d;
        excess[i] += d;
        if (d && excess[i] == d)
            excess_v.push(i);
    }
    void relabel(int u, vector<vector<int>> &flow){
        int d=INT_MAX;
        for(int i=0;i<n;i++){
            if(adjMatrix[u][i]-flow[u][i]>0)
                d=min(d, height[i]);
        }
        if(d<INT_MAX)
            height[u]=d+1;
    }
    void discharge(int u, vector<vector<int>> &flow){
        while(excess[u]>0){
            if(seen[u] < n){
                int v=seen[u];
                if(adjMatrix[u][v]-flow[u][v]>0 && height[u]>height[v])
                    push(u,v,flow);
                else
                    seen[u]++;
            }
            else{
                relabel(u, flow);
                seen[u]=0;
            }
        }
    }
    int pushRelabel(int s=0, int t=-1){
        height[s]=n;
        excess[s]=INT_MAX;
        vector<vector<int>> flow(n,vector<int>(n,0));
        //queue<int> excess_v;
        if(t==-1)t=n-1;
        for (int i = 0; i<n; i++) {
            if (i!=s)
                push(s, i,flow);
        }
        while(!excess_v.empty()){
            int u=excess_v.front();
            excess_v.pop();
            if(u!=s && u!=t)
                discharge(u,flow);
        }
        int max_flow=0;
        for(int i=0;i<n;i++){
            max_flow+=flow[i][t];
        }
        return max_flow;
    }
};
int main()
{
    int v,e;cin>>v>>e;
    GraphAdjList g1(v);
    GraphAdjMatrix g(v);
    int k,m,cap;
    for(int i=0;i<e;i++){
        cin>>k>>m>>cap;
        g.addEdge(k,m,cap);
        g1.addEdge(k,m,cap);
    }
    cout<<g.edmond_karp()<<" "<<g.ford_flukerson()<<" "<<g.dinic()<<" "<<g.pushRelabel();
    cout<<endl;
    g.find_min_cut();
    cout<<endl;
    cout<<g1.edmond_karp()<<" "<<g1.ford_flukerson()<<" "<<g1.dinic()<<" "<<g1.pushRelabel();
    cout<<endl;
    g1.find_min_cut();
    return 0;
}
