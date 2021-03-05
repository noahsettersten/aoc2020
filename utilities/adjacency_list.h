#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H

// stores adjacency list items
struct adjNode {
    int val, cost;
    adjNode* next;
};

// structure to store edges
struct graphEdge {
    int start_ver, end_ver, weight;
};

class AdjacencyList {
  adjNode* getAdjListNode(int value, int weight, adjNode* head);
  int N;  // number of nodes in the graph

public:
  adjNode **head;                //adjacency list as array of pointers

  AdjacencyList(graphEdge edges[], int n, int N);
  ~AdjacencyList();
  // void insertEdge

  void display(adjNode* ptr, int i);
};

#endif
