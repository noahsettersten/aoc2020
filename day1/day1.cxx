#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void usage() {
  cout << "Usage:\n\n";
  cout << "day1 input.txt\n";
}

int sumOf2(vector<int> expenses) {
  for (size_t i = 0; i < expenses.size(); i++) {
    for (size_t j = 0; j < expenses.size(); j++) {
      if (expenses[i] + expenses[j] == 2020) {
        return expenses[i] * expenses[j];
      }
    }
  }

  return -1;
}

int sumOf3(vector<int> expenses) {
  for (size_t i = 0; i < expenses.size(); i++) {
    for (size_t j = 0; j < expenses.size(); j++) {
      for (size_t k = 0; k < expenses.size(); k++) {
        if (expenses[i] + expenses[j] + expenses[k] == 2020) {
          return expenses[i] * expenses[j] * expenses[k];
        }
      }
    }
  }

  return -1;
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

    int result = sumOf3(expenses);
    if (result < 0) {
      cout << "Failed to find numbers that add up to 2020\n";
    } else {
      cout << "Multiplication of numbers that sum 2020: " << result << "\n";
    }
  } else {
    cout << "Failed to read file!";
    return 2;
  }

  return 0;
}
