#include <iostream>
#include "adjacency_list.h"

// Based on https://www.softwaretestinghelp.com/graph-implementation-cpp/

AdjacencyList::AdjacencyList(graphEdge edges[], int numEdges, int numNodes) {
  // allocate new node
  head = new adjNode*[numNodes]();
  this->N = numNodes;

  // initialize head pointer for all vertices
  for (int i = 0; i < numNodes; ++i) {
      head[i] = nullptr;
  }

  // construct directed graph by adding edges to it
  for (int i = 0; i < numEdges; i++)  {
    int start_ver = edges[i].start_ver;
    int end_ver = edges[i].end_ver;
    int weight = edges[i].weight;

    // insert in the beginning
    adjNode* newNode = getAdjListNode(end_ver, weight, head[start_ver]);

                // point head pointer to new node
    head[start_ver] = newNode;
  }
};

AdjacencyList::~AdjacencyList(){
  for (int i = 0; i < N; i++) {
    delete[] head[i];
  }

  delete[] head;
}

// insert new nodes into adjacency list from given graph
adjNode* AdjacencyList::getAdjListNode(int value, int weight, adjNode* head) {
  adjNode* newNode = new adjNode;
  newNode->val = value;
  newNode->cost = weight;

  newNode->next = head;   // point new node to current head
  return newNode;
}

// print all adjacent vertices of given vertex
void AdjacencyList::display(adjNode* ptr, int i)
{
  while (ptr != nullptr) {
    std::cout << "(" << i << ", " << ptr->val
        << ", " << ptr->cost << ") ";
    ptr = ptr->next;
  }

  std::cout << std::endl;
}
