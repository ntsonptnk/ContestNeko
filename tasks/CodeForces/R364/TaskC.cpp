#include "global.hpp"
#include "Scanner.hpp"

struct MyEdge {
    int begin, end, weight;
    MyEdge() {}
    MyEdge(int begin, int end, int weight): begin(begin), end(end), weight(weight) {}
};

class WeightedUndirectedGraph {
public:
    vector<vector<MyEdge>> adj;
    int nNodes;

    WeightedUndirectedGraph(int nNodes): nNodes(nNodes) {
        adj.resize(nNodes);
    }

    void addEdge(int end1, int end2, int weight) {
        adj[end1].push_back(MyEdge(end1, end2, weight));
        adj[end2].push_back(MyEdge(end2, end1, weight));
    }
};

class PathFinder {
    const WeightedUndirectedGraph &graph;
    int source, dest;

    vector<MyEdge> prev;
    vector<bool> visited;

    // Return true if found a path.
    bool dfs(int currentNode, int dest) {
        for (auto &edge: graph.adj[currentNode]) {
            if (!visited[edge.end]) {
                visited[edge.end] = true;
                prev[edge.end] = edge;
                if (edge.end == dest) {
                    return true;
                }
                if (dfs(edge.end, dest)) {
                    return true;
                }
            }
        }
        return false;
    }

public:
    PathFinder(const WeightedUndirectedGraph &graph, int source, int dest) : graph(graph), source(source), dest(dest) {
    }

    // Return empty list if not found a path
    vector<MyEdge> findPath() {
        visited.resize(graph.nNodes);
        prev.resize(graph.nNodes);
        for (int i = 0; i < graph.nNodes; i++) {
            visited[i] = false;
        }
        visited[source] = true;
        bool result = dfs(source, dest);

        vector<MyEdge> edgesInPath;

        if (!result) {
            return edgesInPath;
        }

        int currentNode = dest;
        while (currentNode != source) {
            edgesInPath.push_back(prev[currentNode]);
            currentNode = prev[currentNode].begin;
        }

        reverse(edgesInPath.begin(), edgesInPath.end());
        return edgesInPath;
    }
};


class TaskC {
public:
    void solve(std::istream& inStream, std::ostream& outStream) {
        Scanner in(inStream);
        Writer out(outStream);

        int nNodes, nEdges;
        in >> nNodes >> nEdges;

        WeightedUndirectedGraph graph(nNodes);

        int source, dest;
        in >> source >> dest;
        source--;
        dest--;

        repeat(nEdges) {
            int x, y, w;
            in >> x >> y >> w;
            x--;
            y--;
            graph.addEdge(x, y, w);
        }


        PathFinder pathFinder(graph, source, dest);

        vector<MyEdge> edgesInPath = pathFinder.findPath();

        if (edgesInPath.empty()) {
            // Not connected graph

            outStream << 0;
        } else {
            for (auto &edge : edgesInPath) {
                LOG(1, "Edge: " << edge.begin + 1 << " " << edge.end + 1);
            }
        }

    }
};
