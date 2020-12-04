#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
// using namespace std;

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

bool checkPolicy1(size_t a, size_t b, char policy, std::string password) {
    size_t count = 0;

    // std::cout << "  Matching password " << password << " against min " << a << ", max " << b << " for " << policy << '\n';
    count = std::count(password.begin(), password.end(), policy);

    if (count >= a && count <= b) {
      // std::cout << "  Valid!\n";
      return true;
    }

    return false;
}

bool checkPolicy2(size_t a, size_t b, char policy, std::string password) {
  if ((password.at(a-1) == policy) != (password.at(b-1) == policy)) {
    return true;
  }

  return false;
}

bool validatePassword(std::string line) {
    const std::regex pieces_regex("(\\d+)-(\\d+) (\\w): (.+)");
    std::smatch pieces_match;

    size_t first = 0;
    size_t second = 0;
    char policy;

    std::cout << "Parsing:  " << line << '\n';
    if (std::regex_match(line, pieces_match, pieces_regex)) {
        for (size_t j = 0; j < pieces_match.size(); ++j) {
            std::ssub_match sub_match = pieces_match[j];
            std::string piece = sub_match.str();

            if (j == 1) { first = (size_t)stoi(piece); }
            if (j == 2) { second = (size_t)stoi(piece); }
            if (j == 3) { policy = piece.at(0); }

            if (j == 4) {
              return checkPolicy2(first, second, policy, piece);
            }
        }
    }

    // std::cout << "  INVALID!\n";
    return false;
}

int countValidPasswords(std::vector<std::string> passwords) {
  int result = 0;

  for (size_t i = 0; i < passwords.size(); i++) {
    if (validatePassword(passwords[i])) {
      result++;
    }
  }

  return result;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "Missing input file argument.\n";
    return 1;
  }

  std::vector<std::string> passwords = readFile(argv[1]);

  int result = countValidPasswords(passwords);
  std::cout << "Number of valid passwords: " << result << "\n";

  return 0;
}
