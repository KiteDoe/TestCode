#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;


class Node{
    public:
        int x, y;
        int f, g, h;
        bool obstacle;
        bool closed;
        Node *parent;

        Node(int x, int y, bool obstacle = false) : x(x), y(y), obstacle(obstacle), closed(false), parent(nullptr) {}

        bool isObstacle() const{ 
            return obstacle;
        }
};

int heuristic(Node* start, Node* end){
    return abs(start->x - end->x) + (start->y - end->y);
}

vector<Node*> aSitara(vector<vector<Node>> &grid, Node* start, Node* end){
    
    auto compareNode = [](Node* a, Node* b){
        return a->f > b->f;
    };

    priority_queue<Node *, vector<Node *>, decltype(compareNode)> openList(compareNode);
    set<Node*> openSet;

    start -> g = 0;
    start -> h = heuristic(start, end);
    start -> f = start -> g + start -> h;
    openList.push(start);
    openSet.insert(start);

    while(!openList.empty()){
        Node* current = openList.top();
        openList.pop();

        if(current == end){
            vector<Node*> path;
            while(current != nullptr){
                path.push_back(current);
                current = current -> parent;
            }
            reverse(path.begin(), path.end());
            return path;
        }
        
        current->closed = true;

        for(int dx = -1; dx <= 1 ; dx++){
            for(int dy = -1; dy <=1; dy++){

                if(dx == 0 && dy == 0){
                    continue;
                }

                int x = dx + current -> x;
                int y = dy + current -> y;

                if(x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size()){
                    Node* child = &grid[x][y];

                    if(!child->isObstacle() && !child->closed){
                        int g = current->g + 1;
                        int h = heuristic(child, end);
                        int f = h + g;

                        if(openSet.find(child) != openSet.end() && g >= child->g){
                            continue;
                        }
                        child-> parent = current;
                        child->g = g;
                        child->h = h;
                        child->f = f;
                        openList.push(child);
                        openSet.insert(child);
                    }
                }
            }
        }
    }
    return {};
}

void display(const vector<vector<Node>> &grid){
    vector<Node> obstacle;

    for(const auto &i : grid){
        for(const auto &node : i){
            if(node.obstacle){
                cout << "O ";
                obstacle.push_back(node);
            }
            else{
                cout << "- ";
            }
        }
        cout << endl;
    }
    cout << endl;
    cout << "Obstacles list:" << endl;
    for(const auto &node : obstacle){
        cout << "Obstacle at (" << node.x << ", " << node.y << ")" << endl;
    }
    cout << endl;
}

void displayPathGrid(const vector<vector<Node>> &grid, vector<Node*> path){
    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j < grid[i].size(); j++){
            if(grid[i][j].obstacle){
                cout << "O ";
            }
            else if(find(path.begin(), path.end(), &grid[i][j]) != path.end()){
                cout << "* ";
            }
            else{
                cout << "- ";
            }
        }
        cout << endl;
    }
    cout << endl;
}


int main(){
    vector<vector<Node>> grid(10, vector<Node>(10, Node(0, 0)));
    Node* start;
    Node* end;

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            grid[i][j] = Node(i , j);
        }
    }
    int choice;
    cout << "1. Keep start position (0, 0) and end position (9, 9)" << endl;
    cout << "2. Enter customer start and end" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    if(choice == 1){
        start = &grid[0][0];
        end = &grid[9][9];
    }
    else{
        int start_x, start_y, end_x, end_y;
        cout << "Enter x and y coordinate for start: ";
        cin >> start_x >> start_y;
        cout << "Enter x and y coordinate for end: ";
        cin >> end_x >> end_y;

        start = &grid[start_x][start_y];
        end = &grid[end_x][end_y];
    }

    int obstacleCount;
    cout << "Enter obstacle count: ";
    cin >> obstacleCount;

    for(int i = 0; i < obstacleCount; i++){
        int row, col;
        cout << "Enter position of obstacle " << i+1 << ": ";
        cin >> row >> col;
        grid[row][col].obstacle = true;
    }

    vector<Node*> path = aSitara(grid, start, end);

    display(grid);

    if(!path.empty()){
        cout << "Path found:" << endl;
        for(auto &node : path){
            cout << "(" << node->x << ", " << node->y << ")" << endl;
        }
        displayPathGrid(grid, path);
    }
    else{
        cout << "No path found" << endl;
    }

    return 0;
}