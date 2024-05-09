#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

const int INF = 1e9;

typedef pair<int, int> pii;
typedef vector<vector<pii>> Graph;

vector<int> dijkstras(const Graph &graph, int source){
    int n = graph.size();
    vector<int> dist(n, INF);
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    dist[source]=0;
    pq.push({0, source});

    while(!pq.empty()){
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if(d > dist[u])
            continue;
        
        for(auto &edge: graph[u]){
            int v = edge.first;
            int w = edge.second;

            if(dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

vector<pair<pair<int,int>, int>> prims(const Graph &graph, int source, int &totalCost){
    int n = graph.size();
    vector<bool> visited(n , false);
    vector<int> parent(n , -1);
    vector<int> weight(n , INF);
    vector<pair<pair<int, int>, int>> mstEdges;

    totalCost = 0;
    weight[source] = 0;
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    pq.push({0, source});

    while(!pq.empty()){
        int u = pq.top().second;
        pq.pop();

        if(visited[u])
            continue;
        
        visited[u] = true;

        if(parent[u] != -1){
            mstEdges.push_back({{parent[u], u}, weight[u]});
        }
        totalCost += weight[u];
        for(const auto &edge: graph[u]){
            int v = edge.first;
            int w = edge.second;

            if(!visited[v] && w < weight[v]){
                parent[v] = u;
                weight[v] = w;
                pq.push({w, v});
            }
        }
    }
    return mstEdges;
}


int main(){
    int n, m;
    cout << "Enter number of router and paths: ";
    cin >> n >> m;

    Graph graph(n);
    map<char, int> vertexIndex;

    cout << "Enter labels for routers: ";
    for(int i = 0; i < n; i++){
        char labels;
        cin >> labels;
        vertexIndex[labels] = i;
    }

    cout << "Enter router links:";
    for(int i = 0; i < m; i++){
        char from, to;
        int weight;
        cin >> from >> to >> weight;
        graph[vertexIndex[from]].push_back({vertexIndex[to], weight});
        graph[vertexIndex[to]].push_back({vertexIndex[from], weight});
    }

    char sourceLabel, destLabel;
    cout << "Enter source router: ";
    cin >> sourceLabel;
    int source = vertexIndex[sourceLabel];

    int totalCost;
    vector<pair<pair<int,int>, int>> mstEdges = prims(graph, source, totalCost);


    cout << "Minimal Spanning tree: ";
    for(auto &edge : mstEdges){
        char from = edge.first.first + 'A';
        char to = edge.first.second + 'A';
        int weight = edge.second;

        cout << from << " - " << to << " (Weight: " << weight << ")" << endl; 
    }
    cout << "Total cost of MST: " << totalCost;
}