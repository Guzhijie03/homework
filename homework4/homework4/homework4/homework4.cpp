#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>

class Graph {
private:
    int numVertices;
    std::vector<std::vector<bool>> adj;

public:
    Graph(int numVertices) {
        this->numVertices = numVertices;
        adj.resize(numVertices, std::vector<bool>(numVertices, false));
    }

    void addEdge(int src, int dest) {
        adj[src][dest] = true;
        adj[dest][src] = true;
    }

    void printGraph() const {
        for (int i = 0; i < numVertices; ++i) {
            for (int j = 0; j < numVertices; ++j) {
                std::cout << (adj[i][j] ? "1 " : "0 ");
            }
            std::cout << std::endl;
        }
    }

    void BFS(int startVertex) const {
        std::vector<bool> visited(numVertices, false);
        std::queue<int> q;
        visited[startVertex] = true;
        q.push(startVertex);

        std::cout << "执行 BFS 遍历操作: ";

        while (!q.empty()) {
            int currentVertex = q.front();
            q.pop();
            std::cout << currentVertex << " ";

            for (int neighbor : adj[currentVertex]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }

        std::cout << std::endl;
    }

    void DFS(int startVertex) const {
        std::vector<bool> visited(numVertices, false);
        std::stack<int> s;
        s.push(startVertex);

        std::cout << "执行 DFS 遍历操作: ";

        while (!s.empty()) {
            int currentVertex = s.top();
            s.pop();

            if (!visited[currentVertex]) {
                visited[currentVertex] = true;
                std::cout << currentVertex << " ";

                for (int neighbor : adj[currentVertex]) {
                    if (!visited[neighbor]) {
                        s.push(neighbor);
                    }
                }
            }
        }

        std::cout << std::endl;
    }

    std::vector<int> Dijkstra(int sourceVertex) const {
        std::vector<int> distances(numVertices, std::numeric_limits<int>::max());
        distances[sourceVertex] = 0;

        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
        pq.push(std::make_pair(0, sourceVertex));

        while (!pq.empty()) {
            int currentVertex = pq.top().second;
            int currentDistance = pq.top().first;
            pq.pop();

            if (currentDistance > distances[currentVertex]) {
                continue;
            }

            for (int neighbor : adj[currentVertex]) {
                int neighborDistance = 1; 

                if (currentDistance + neighborDistance < distances[neighbor]) {
                    distances[neighbor] = currentDistance + neighborDistance;
                    pq.push(std::make_pair(distances[neighbor], neighbor));
                }
            }
        }

        return distances;
    }

    std::vector<std::pair<int, int>> Prim() const {
        std::vector<std::pair<int, int>> minSpanningTree;
        std::vector<bool> visited(numVertices, false);

        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
        pq.push(std::make_pair(0, 0));

        while (!pq.empty()) {
            int currentVertex = pq.top().second;
            int currentWeight = pq.top().first;
            pq.pop();

            if (visited[currentVertex]) {
                continue;
            }

            visited[currentVertex] = true;

            if (currentVertex != 0) {
                minSpanningTree.emplace_back(currentVertex, currentWeight);
            }

            for (const auto& neighbor : adj[currentVertex]) {
                int neighborVertex = neighbor;
                int neighborWeight = 1; 

                if (!visited[neighborVertex]) {
                    pq.push(std::make_pair(neighborWeight, neighborVertex));
                }
            }
        }

        return minSpanningTree;
    }
};

int main() {
    Graph graph(7);

    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 3);
    graph.addEdge(2, 4);
    graph.addEdge(3, 4);
    graph.addEdge(3, 5);
    graph.addEdge(4, 5);
    graph.addEdge(4, 6);
    graph.addEdge(5, 6);

    graph.printGraph();

    graph.BFS(0);
    graph.DFS(0);

    std::vector<int> shortestDistances = graph.Dijkstra(0);
    std::cout << "使用Dijkstra算法从源顶点0计算最短路径距离的操作:" << std::endl;
    for (int i = 0; i < shortestDistances.size(); ++i) {
        std::cout << "Vertex " << i << ": " << shortestDistances[i] << std::endl;
    }

    std::vector<std::pair<int, int>> minSpanningTree = graph.Prim();
    std::cout << "使用Prim算法构建最小支撑树:" << std::endl;
    for (const auto& edge : minSpanningTree) {
        std::cout << edge.first << " - " << edge.second << std::endl;
    }

    return 0;
}
