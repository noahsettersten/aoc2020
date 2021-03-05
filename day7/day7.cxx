#include <iostream>
#include <regex>
#include <string>
#include <sstream>
#include "adjacency_list.h"
#include "file_helpers.h"
#include "string_helpers.h"
using namespace std;

// Create graph representation (adjacency matrix?).
// Read and parse file into rep.
// Plot possible outcomes for bag.

void testGraph() {
  // graph edges array.
  graphEdge edges[] = {
      // (x, y, w) -> edge from x to y with weight w
      {0,1,2},{0,2,4},{1,4,3},{2,3,2},{3,1,4},{4,3,3}
  };
  int numNodes = 6;      // Number of vertices in the graph
  // calculate number of edges
  int numEdges = sizeof(edges)/sizeof(edges[0]);
  // construct graph
  AdjacencyList graph(edges, numEdges, numNodes);
  // print adjacency list representation of graph
  cout <<"Graph adjacency list "<< endl << "(start_vertex, end_vertex, weight):" << endl;
  for (int i = 0; i < numNodes; i++)
  {
      // display adjacent vertices of vertex i
      graph.display(graph.head[i], i);
  }
}

vector<string> parseContents(string contentString) {
  // Contents regex:
  // 1: Number
  // 2: style and color
  const std::regex contents_regex("([a-z]+ [a-z]+)");
                                    // (\d+) ([a-z]+ [a-z]+)
  std::smatch contents_match;

  stringstream ss(contentString);
  vector<string> contents;
  string item;

  cout << endl << "contentString: " << contentString << endl;
  while(getline(ss, item, ',')) {
    cout << endl << "item: " << item << endl;
    if(std::regex_match(item, contents_match, contents_regex)) {
      cout << endl << "[0]: " << contents_match[0] << endl;
      cout << endl << "[0]: " << contents_match[1] << endl;
      cout << endl << "[0]: " << contents_match[2] << endl;
      // ssub_match subMatch = contents_match[1];
      // string contentsCount = subMatch.str();

      ssub_match kindMatch = contents_match[2];
      string containerKind = kindMatch.str();

      // trim(containerKind);
      cout << endl << "containerKind: " << containerKind << endl;
      contents.push_back(containerKind);
    }
  }

  return contents;
}

void parseLine(string line) {
  // Line-level regex:
  // 1: style and color
  // 2: bag contents
  const std::regex line_regex("^([a-z]+ [a-z]+) bags contain (.*)$");
  std::smatch line_match;

  if(std::regex_match(line, line_match, line_regex)) {
    ssub_match subMatch = line_match[1];
    string containerStyle = subMatch.str();

    ssub_match contentsMatch = line_match[2];
    string containerContents = contentsMatch.str();
    vector<string> contents = parseContents(containerContents);

    cout << "Bag - Style: " << containerStyle << ", Can Hold:" << endl;
    for (size_t i = 0; i < contents.size(); i++) {
      cout << "  - " << contents[i] << endl;
    }

    cout << endl;
  }
}

int countValidBags(vector<string> lines) {

  for (size_t i = 0; i < lines.size(); i++) {
    parseLine(lines[i]);
  }

  // TODO
  return (int)lines.size();
}

int main(int argc, char **argv) {
  if (argc < 2) {
    cout << "Missing input file argument.\n";
    return 1;
  }

  vector<string> lines = readFile(argv[1]);

  int result = countValidBags(lines);
  cout << "Number of bags that can hold a shiny gold bag: " << result << "\n";

  // testGraph();
  return 0;
}

// (start_vertex, end_vertex, weight):
// (0, 2, 4)
// (0, 1, 2)
// (1, 4, 3)
// (2, 3, 2)
// (3, 1, 4)
// (4, 3, 3)
