#include <iostream>
#include <vector>

enum Status { NEW, VISITED, DONE };

class Node {
 public:
  unsigned int index;
  Status status;
  int distance;
  Node *predecessor;
  Node(unsigned int);
  void Init(unsigned int);
};

Node::Node(unsigned int idx) {
  Init(idx);
}

void Node::Init(unsigned int idx) {
  status = NEW;
  distance = -1;
  predecessor = NULL;
  index = idx;
}

class Graph {
  public:
  Graph(std::vector<std::vector<unsigned int>>);
  void GetCycles(std::vector<std::vector<unsigned int>> &);
  unsigned int GetNodesCount();
  void Init();

  private:
  std::vector<Node *> nodes;
  std::vector<std::vector<unsigned int>> edges;
  Node *GetNode(unsigned int);
  bool IsAdjacent(unsigned int, unsigned int);
  void DfsFindCycle(unsigned int, unsigned int, std::vector<std::vector<unsigned int>> &, std::vector<unsigned int>);
};

Graph::Graph(std::vector<std::vector<unsigned int>> edges) {
  for (int i = 0; i < edges[0].size(); i++) {
    nodes.push_back(new Node(i));
  }

  this->edges = edges;
}

bool Graph::IsAdjacent(unsigned int prim_node_idx, unsigned int adj_node_idx) {
  return (bool) edges[prim_node_idx][adj_node_idx];
}

Node *Graph::GetNode(unsigned int index) {
  return nodes[index];
}

unsigned int Graph::GetNodesCount() {
  return nodes.size();
}

void Graph::Init() {
  for (int i = 0; i < GetNodesCount(); i++) {
    Node *n = GetNode(i);
    n->Init(i);
  }
}

void Graph::GetCycles(std::vector<std::vector<unsigned int>> &cycles) {
  for (int i = 0; i < GetNodesCount(); i++) {
    Init();
    Node *u = GetNode(i);
    std::vector<unsigned int> path;
    DfsFindCycle(i, i, cycles, path);
  }
}

void Graph::DfsFindCycle(unsigned int index, unsigned int root, std::vector<std::vector<unsigned int>> &cycles, std::vector<unsigned int> path) {
  Node *u = GetNode(index);
  u->status = VISITED;
  path.push_back(index);
  for (int i = 0; i < GetNodesCount(); i++) {
    if (IsAdjacent(index, i)) {
      if (i == root) {
        path.push_back(root);
        cycles.push_back(path);
      }
      Node *v = GetNode(i);
      if (v->status == NEW) {
        v->predecessor = u;
        DfsFindCycle(v->index, root, cycles, path);
      }
    }
  }
  u->status = DONE;
}

void printCycles(std::vector<std::vector<unsigned int>> &cycles) {
  if (cycles.empty()) return;
  
  for (auto it: cycles) {
    for (unsigned int i = 0; i < it.size(); i++) {
      std::cout << it.at(i);
      if (i < it.size() - 1) std::cout << " -> ";
    }
    std::cout << std::endl;
  }
}

int main() {
  std::vector<std::vector<unsigned int>> cycles;

  std::vector<std::vector<unsigned int>> edges_table {
    {1, 1, 1},
    {0, 0, 1},
    {0, 1, 0}
  };

  Graph g(edges_table);
  g.GetCycles(cycles);

  std::cout << "Cycles:" << std::endl;
  printCycles(cycles);

  return 0;
}