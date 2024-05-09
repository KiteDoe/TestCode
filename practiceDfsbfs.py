from collections import defaultdict, deque

class Graph:
    def __init__(self):
        self.graph = defaultdict(list)

    def addNode(self, nodeVal):
        if nodeVal not in self.graph:
            self.graph[nodeVal] = []

    def addEdge(self, u, v):
        self.graph[u].append(v)
        self.graph[v].append(u)

    def displayGraph(self):
        print("Current State of Graph: \n")
        for node, neighbours in self.graph.items():
            print(f"Node {node} connects to: {neighbours}")

    def dfs(self, start, end, path=[], level=0):
        path = path + [start]
        print(f"Node {start} at level {level}")

        if start == end:
            return path
        
        for neighbour in self.graph[start]:
            if neighbour not in path:
                new_path = self.dfs(neighbour, end, path, level+1)
                if new_path:
                    return new_path
            
        return None

    def bfs(self, start, end):
        queue = deque([(start, [start])])
        levels = {start : 0}

        while queue:
            current, path = queue.popleft()
            level = levels[current]
            print(f"Node {current} at level {level}")

            for neighbour in self.graph[current]:
                if neighbour not in path:
                    new_path = path + [neighbour]
                    levels[neighbour] = level + 1
                    if neighbour == end:
                        return new_path, levels
                    else:
                        queue.append((neighbour, new_path))
        return None, None

        
# Driver code
network = Graph()

noNodes = int(input("Enter number of nodes: "))
for _ in range(noNodes):
    nodeVal = int(input("Enter node value: "))
    network.addNode(nodeVal)

noEdges = int(input("Enter number of edges: "))
for _ in range(noEdges):
    u, v = map(int, input("Enter the edges(u, v): ").split())
    network.addEdge(u, v)

start = int(input("Enter start node: "))
end = int(input("Enter end node: "))

if start in network.graph and end in network.graph:
    dfs_path = network.dfs(start, end)
    print(f"DFS path: {dfs_path}")
    print("\n")


if start in network.graph and end in network.graph:
    bfs_path = network.bfs(start, end)
    print(f"BFS path: {bfs_path}")
    print("\n")

network.displayGraph()