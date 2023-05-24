#include <iostream>
#include <vector>
#include <queue>

struct adjNode {
    int end_vert;
    int cost;
    adjNode* next;
};

struct graphEdge {
    int start_vert;
    int end_vert;
    int weight;
};

class DirGraph {
private:
    std::vector<adjNode*> nodes;
    std::vector<int> inDegree;
    std::vector<int> topNum;

    adjNode* addEdge(int end_vert, int weight, adjNode* head) {
        adjNode* newNode = new adjNode;
        newNode->end_vert = end_vert;
        newNode->cost = weight;
        newNode->next = head;
        return newNode;
    }

public:
    DirGraph(graphEdge edges[], int numVert, int NumEdges) {
        nodes.resize(numVert, nullptr);
        inDegree.resize(numVert, 0);
        topNum.resize(numVert, 0);

        for (int i = 0; i < NumEdges; ++i) {
            int start_vert = edges[i].start_vert;
            int end_vert = edges[i].end_vert;
            int weight = edges[i].weight;
            adjNode* newNode = addEdge(end_vert, weight, nodes[start_vert]);
            nodes[start_vert] = newNode;
            inDegree[end_vert]++;
        }
    }

    ~DirGraph() {
        for (auto& node : nodes) {
            while (node != nullptr) {
                adjNode* next = node->next;
                delete node;
                node = next;
            }
        }
    }

    void topologicalSort() {
        std::queue<int> q;
        int count = 0;

        for (int i = 0; i < nodes.size(); ++i) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            topNum[count++] = v;

            adjNode* temp = nodes[v];
            while (temp != nullptr) {
                if (--inDegree[temp->end_vert] == 0) {
                    q.push(temp->end_vert);
                }
                temp = temp->next;
            }
        }

        if (count != nodes.size()) {
            std::cout << "Graph is cyclic, thus can't be sorted.";
            return;
        }

        for (int i = 0; i < nodes.size(); ++i) {
            std::cout <<"Vertex "<<i<<" has topNum:"<<topNum[i]+1 << '\n';
        }
    }
};

int main() {
    graphEdge edges[] = { {0,1,2},{0,2,4},{1,3,3},{2,3,2},{3,4,4} };
    int N = 5;
    DirGraph graph{ edges, N, 5 };
    graph.topologicalSort();
    return 0;
}