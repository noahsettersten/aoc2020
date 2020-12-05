#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
using namespace std;

vector<string> readFile(char* filename) {
  vector<string> v;
  ifstream file(filename);

  if (!file.good()) {
    cout << "Failed to read file!";
    return v;
  }

  for (string line; getline(file, line); ) {
    v.push_back(line);
  }

  file.close();

  return v;
}

int countTreesHit(vector<string> map, int xSlope, int ySlope) {
  int result = 0;
  int x = 0;

  // Assume the whole map is the same width
  int mapWidth = map[0].length();

  for (size_t y = 0; y < map.size(); y+= ySlope) {
    string row = map[y];

    char destination = row.at(x % mapWidth);
    if (destination == '#') { result++; }

    x += xSlope;
  }

  return result;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    cout << "Missing input file argument.\n";
    return 1;
  }

  vector<string> map = readFile(argv[1]);

  int result1 = countTreesHit(map, 1, 1);
  // Right 3, down 1
  int result2 = countTreesHit(map, 3, 1);
  int result3 = countTreesHit(map, 5, 1);
  int result4 = countTreesHit(map, 7, 1);
  int result5 = countTreesHit(map, 1, 2);

  cout << "Number of trees hit (1, 1): " << result1 << "\n";
  cout << "Number of trees hit (3, 1): " << result2 << "\n";
  cout << "Number of trees hit (5, 1): " << result3 << "\n";
  cout << "Number of trees hit (7, 1): " << result4 << "\n";
  cout << "Number of trees hit (1, 2): " << result5 << "\n";

  cout << "Multiplied: " << (result1 * result2 * result3 * result4 * result5) << "\n";

  return 0;
}
