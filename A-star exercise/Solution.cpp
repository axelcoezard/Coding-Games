#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <limits>

struct Edge
{
    uint32_t neighborId;
    uint32_t cost;
};

struct Node
{
    uint32_t id;

    uint32_t gValue;
    uint32_t hValue;
    uint32_t fValue;

    std::vector<Edge> neighbors;
};

struct NodeComparator
{
    bool operator()(const Node* lhs, const Node* rhs) const
    {
        if (lhs->fValue == rhs->fValue)
            return lhs->id > rhs->id;
        return lhs->fValue > rhs->fValue;
    }
};

typedef std::unordered_map<uint32_t, Node> Graph;

bool aStar(Graph& graph, uint32_t startId, uint32_t goalId)
{
    std::priority_queue<Node*, std::vector<Node*>, NodeComparator> openSet;
    std::unordered_set<uint32_t> closedSet;

    graph[startId].gValue = 0;
    graph[startId].fValue = graph[startId].hValue;

    openSet.push(&graph[startId]);

    while (!openSet.empty())
    {
        Node* current = openSet.top();
        openSet.pop();

        if (closedSet.find(current->id) != closedSet.end())
            continue;

        closedSet.insert(current->id);

        std::cout << current->id << " " << current->fValue << "\n";

        if (current->id == goalId)
            return true;

        for (auto& neighbor : current->neighbors)
        {
            uint32_t neighborId = neighbor.neighborId;
            uint32_t cost = neighbor.cost;
            uint32_t tentative_gValue = current->gValue + cost;

            if (tentative_gValue < graph[neighborId].gValue)
            {
                graph[neighborId].gValue = tentative_gValue;
                graph[neighborId].fValue = graph[neighborId].gValue + graph[neighborId].hValue;
                openSet.push(&graph[neighborId]);
            }
        }
    }
    return false;
}

int main()
{
    uint32_t nodesCount, edgesCount, startId, goalId;

    std::cin >> nodesCount;
    std::cin >> edgesCount;
    std::cin >> startId;
    std::cin >> goalId;
    std::cin.ignore();

    Graph graph;

    for (uint32_t i = 0; i < nodesCount; i++)
    {
        uint32_t heuristic;
        std::cin >> heuristic;
        std::cin.ignore();

        graph[i] = {
            .id = i,
            .gValue = std::numeric_limits<uint32_t>::max(),
            .hValue = heuristic,
            .fValue = std::numeric_limits<uint32_t>::max(),
            .neighbors = {}
        };
    }

    for (uint32_t i = 0; i < edgesCount; i++)
    {
        uint32_t x, y, c;
        std::cin >> x >> y >> c;
        std::cin.ignore();
        
        graph[x].neighbors.push_back({y, c});
        graph[y].neighbors.push_back({x, c});
    }

    aStar(graph, startId, goalId);
}
