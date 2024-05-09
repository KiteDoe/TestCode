#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

int INF = 1e9;
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

int main(){
    int n, m;
    cout << "Enter the number of routers and paths: ";
    cin >> n >> m;

    Graph graph(n);
    map<char, int> vertexIndex;

    cout << "Enter router names for " << n << " nodes:" << endl;
    for(int i = 0; i < n; i++){
        char label;
        cin >> label;
        vertexIndex[label] = i;
    }

    cout << "Enter paths (from to weight):" << endl;
    for(int i = 0; i < m; i++){
        char from, to;
        int weight;
        cin >> from >> to >> weight;
        graph[vertexIndex[from]].push_back({vertexIndex[to], weight});
        graph[vertexIndex[to]].push_back({vertexIndex[from], weight});
    }

    char sourceNode, destNode;

    cout << "Enter source node:";
    cin >> sourceNode;
    int source = vertexIndex[sourceNode];

    vector<int> distances = dijkstras(graph, source);

    cout << "Do you want to calculate the Shortest Path to a specific destination? (Y/N): ";
    char choice;
    cin >> choice;

    if(toupper(choice) == 'Y'){
        cout << "Enter destination router:";
        cin >> destNode;
        int destination = vertexIndex[destNode];

        cout << "Shortest Distance from Router " << sourceNode << " to Router " << destNode << " is: ";
        if(distances[destination] == INF){
            cout << "INF" << endl;
        }
        else{
            cout << distances[destination] << endl;
        }
    }
    else{
        cout << "Shortest Distances from Router " << sourceNode << ":" << endl;
        for(const auto &pair: vertexIndex){
            char label = pair.first;
            int index = pair.second;
            cout << "Router " << label << ":";
            if(distances[index] == INF){
            cout << "INF" << endl;
            }
            else{
                cout << distances[index] << endl;
            }
        }
    }

    return 0;
}
