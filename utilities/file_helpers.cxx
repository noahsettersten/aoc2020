#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> readFile(char* filename) {
  std::vector<std::string> v;
  std::ifstream file(filename);

  if (!file.good()) {
    std::cout << "Failed to read file!";
    return v;
  }

  for (std::string line; std::getline(file, line); ) {
    v.push_back(line);
  }

  file.close();

  return v;
}
