#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <limits>

struct Node
{
    uint32_t id;

    uint32_t gValue;
    uint32_t hValue;
    uint32_t fValue;

    std::vector<std::pair<uint32_t, uint32_t>> neighbors;
};

struct NodeComparator
{
    bool operator()(const Node& lhs, const Node& rhs) const {
        return lhs.fValue > rhs.fValue;
    }
};

typedef std::unordered_map<uint32_t, Node> Graph;

std::array<uint32_t, 4> ParseInformations()
{
    uint32_t nodesCount, edgesCount, startId, goalId;
    std::cin >> nodesCount;
    std::cin >> edgesCount;
    std::cin >> startId;
    std::cin >> goalId;
    std::cin.ignore();
    return {nodesCount, edgesCount, startId, goalId};
}

bool aStar(Graph& graph, uint32_t startId, uint32_t goalId)
{
    std::priority_queue<Node, std::vector<Node>, NodeComparator> openSet;

    std::function<uint32_t(uint32_t)> heuristic = [](uint32_t a) -> uint32_t { return a; };

    graph[startId].gValue = 0;
    graph[startId].hValue = heuristic(graph[startId].hValue);
    graph[startId].fValue = graph[startId].hValue;

    openSet.push(graph[startId]);

    while (!openSet.empty())
    {
        Node current = openSet.top();
        openSet.pop();

        std::cout << current.id << " " << current.fValue << std::endl;

        if (current.id == goalId)
            return true;

        for (auto& neighbor : current.neighbors)
        {
            uint32_t neighborId = neighbor.first;
            uint32_t cost = neighbor.second;
            uint32_t tentative_gValue = current.gValue + cost;

            if (tentative_gValue < graph[neighborId].gValue)
            {
                graph[neighborId].gValue = tentative_gValue;
                graph[neighborId].hValue = heuristic(graph[neighborId].hValue);
                graph[neighborId].fValue = graph[neighborId].gValue + graph[neighborId].hValue;
                openSet.push(graph[neighborId]);
            }
        }
    }

    return false;
}

int main()
{
    auto [nodesCount, edgesCount, startId, goalId] = ParseInformations();

    std::cerr << "Nodes count: " << nodesCount << std::endl;
    std::cerr << "Edges count: " << edgesCount << std::endl;
    std::cerr << "Start id: " << startId << std::endl;
    std::cerr << "Goal id: " << goalId << std::endl;

    Graph graph;

    for (uint32_t i = 0; i < nodesCount; i++)
    {
        uint32_t heuristic;
        std::cin >> heuristic;

        graph[i].id = i;
        graph[i].hValue = heuristic;
        graph[i].gValue = std::numeric_limits<uint32_t>::max();
        graph[i].fValue = std::numeric_limits<uint32_t>::max();

        std::cerr << "Added node " << i << " h:" << graph[i].hValue << " g:" << graph[i].gValue << " f:" << graph[i].fValue << std::endl;
    }

    for (uint32_t i = 0; i < edgesCount; i++)
    {
        uint32_t x,  y,  c;
        std::cin >> x >> y >> c;
        std::cin.ignore();
        
        graph[x].neighbors.push_back({y, c});
        graph[y].neighbors.push_back({x, c});

        std::cerr << "Added edge " << x << " <-> " << y << " = " << c << std::endl;
    }

    aStar(graph, startId, goalId);
}