#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void usage() {
  cout << "Usage:\n\n";
  cout << "day1 input.txt\n";
}

int main(int argc, char **argv) {
  if (argc < 2) {
    cout << "Missing input file argument.\n";
    usage();
    return 1;
  }

  vector<int> expenses;
  ifstream file(argv[1]);

  if (file.good()) {
    int current = 0;
    while (file >> current) {
      expenses.push_back(current);
    }

    file.close();

    cout << "Input data:\n";
    for (size_t i = 0; i < expenses.size(); i++) {
      cout << expenses[i] << ", ";
    }
  } else {
    cout << "Failed to read file!";
    return 2;
  }

  return 0;
}
