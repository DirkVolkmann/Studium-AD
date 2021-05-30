#include <queue>
#include <iostream>
#include <vector>

enum Color { WHITE, BLACK, GREY };

class Node {
 public:
  unsigned int index;
  Color color;
  int distance;
  Node *predecessor;
  Node(unsigned int);
  void Init(unsigned int);
};

Node::Node(unsigned int idx) {
  Init(idx);
}

void Node::Init(unsigned int idx) {
  color = WHITE;
  distance = -1;
  predecessor = NULL;
  index = idx;
}

class Graph {
  public:
  Graph(std::vector<std::vector<unsigned int>>);
  Node *GetNode(unsigned int);
  bool IsAdjacent(unsigned int, unsigned int);
  void BreadthFirstSearch(unsigned int);
  void DownFirstSearch();
  unsigned int GetNodesCount();
  void PrintTraversal();
  void Init();

  private:
  std::vector<Node *> nodes;
  std::vector<std::vector<unsigned int>> edges;
  std::vector<unsigned int> traversal;
  void DownFirstSearchVisit(unsigned int);
};

Graph::Graph(std::vector<std::vector<unsigned int>> edges) {
  for (int i = 0; i < 9; i++) {
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
  traversal.clear();
  for (int i = 0; i < GetNodesCount(); i++) {
    Node *n = GetNode(i);
    n->Init(i);
  }
}

void Graph::BreadthFirstSearch(unsigned int v0_index) {
  Node *v0 = GetNode(v0_index);
  v0->color = GREY;
  v0->distance = 0;
  v0->predecessor = NULL;

  std::queue<Node*> Q;
  Q.push(v0);
  
  while (!Q.empty()) {
    //std::cout << "Queue size: " << Q.size() << std::endl;

    Node *u = Q.front();
    Q.pop();

    unsigned int index = u->index;
    //std::cout << "Current node: " << index << std::endl << std::endl;
    traversal.push_back(index);

    for (int i = 0; i < GetNodesCount(); i++) {
      if (IsAdjacent(index, i)) {
        Node *v = GetNode(i);
        
        /*std::cout << "Checking Node " << v->index << ": color = " << v->color << " | distance = " << v->distance;
        if (v->predecessor != NULL) std::cout << " | predecessor = " << v->predecessor->index;
        std::cout << std::endl;*/

        if (v->color == WHITE) {
          v->color = GREY;
          v->distance = u->distance + 1;
          v->predecessor = u;
          Q.push(v);
          
          //std::cout << "New values: color = " << v->color << " | distance = " << v->distance << " | predecessor = " << v->predecessor->index << std::endl;
        }
        //std::cout << "---------------------------------------------------" << std::endl;
      }
    }
    u->color = BLACK;
  }
}

void Graph::DownFirstSearch() {
  for (int i = 0; i < GetNodesCount(); i++) {
    Node *u = GetNode(i);
    if (u->color == WHITE) {
      traversal.push_back(i);
      DownFirstSearchVisit(i);
    }
  }
}

void Graph::DownFirstSearchVisit(unsigned int index) {
  Node *u = GetNode(index);
  u->color = GREY;
  for (int i = 0; i < GetNodesCount(); i++) {
    if (IsAdjacent(index, i)) {
      Node *v = GetNode(i);
      if (v->color == WHITE) {
        traversal.push_back(i);
        v->predecessor = u;
        DownFirstSearchVisit(v->index);
      }
    }
  }
  u->color = BLACK;
}

void Graph::PrintTraversal() {
  unsigned int printed = 0;
  while (1) {
    for (int i = 0; i < GetNodesCount(); i++) {
      std::cout << traversal.at(i);
      printed++;
      if (printed == GetNodesCount()) {
        std::cout << std::endl;
        return;
      }
      std::cout << ", ";
    }
  }
}

int main() {

  std::vector<std::vector<unsigned int>> v {
    {0, 1, 1, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0},
    {1, 0, 0, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0},
    {1, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 1, 0, 0, 0}
  };

  Graph g(v);
  g.BreadthFirstSearch(0);
  std::cout << "BFS traversal: ";
  g.PrintTraversal();

  g.Init();
  g.DownFirstSearch();
  std::cout << "DFS traversal: ";
  g.PrintTraversal();

  return 0;
}