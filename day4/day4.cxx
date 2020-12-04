#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <vector>

std::vector<std::string> readFile(char* filename) {
  std::vector<std::string> v;
  std::ifstream file(filename);

  if (!file.good()) {
    std::cout << "Failed to read file!";
    return v;
  }

  std::string passport;
  for (std::string line; std::getline(file, line); ) {
    passport += " ";
    passport += line;

    if (line.length() == 0) {
      v.push_back(passport);
      passport = "";
    }
  }

  v.push_back(passport);

  file.close();

  return v;
}

std::vector<std::string> tokenize(std::string entry, char delim) {
  std::vector<std::string> elements;

  std::replace(entry.begin(), entry.end(), '\n', ' ');

  std::stringstream ss(entry);
  std::string item;

  while(std::getline(ss, item, delim)) {
    elements.push_back(item);
  }

  return elements;
}


bool fieldsPresent(std::vector<std::string> elements) {
  int count = 0;

  for (size_t i = 0; i < elements.size(); i++) {
    if (elements[i].length() == 0 || elements[i].at(0) == 'c') {
      continue;
    }

    count++;
  }

  return count >= 7;
}

bool between(std::string value, int min, int max) {
  int val = stoi(value);

  return val >= min && val <= max;
}

bool endWith(std::string const &fullString, std::string const &ending) {
  if (fullString.length() >= ending.length()) {
    return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
  } else {
    return false;
  }
}

bool fieldValid(std::vector<std::string> pair) {
  if (pair[0] == "byr") {
    // byr (Birth Year) - four digits; at least 1920 and at most 2002.
    return between(pair[1], 1920, 2002);
  } else if (pair[0] == "iyr") {
    // iyr (Issue Year) - four digits; at least 2010 and at most 2020.
    return between(pair[1], 2010, 2020);
  } else if (pair[0] == "eyr") {
    // eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
    return between(pair[1], 2020, 2030);
  } else if (pair[0] == "hgt") {
    // hgt (Height) - a number followed by either cm or in:
    // If cm, the number must be at least 150 and at most 193.
    // If in, the number must be at least 59 and at most 76.
    if (endWith(pair[1], "in")) {
      return between(pair[1], 59, 76);
    } else if(endWith(pair[1], "cm")) {
      return between(pair[1], 150, 193);
    } else {
      return false;
    }
  } else if (pair[0] == "hcl") {
    // hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
    const std::regex hair_regex("#[0-9a-fA-F]{6}");
    return std::regex_match(pair[1], hair_regex);
  } else if (pair[0] == "ecl") {
    // ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
    std::vector<std::string> eyeColors{ "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };
    return std::find(eyeColors.begin(), eyeColors.end(), pair[1]) != eyeColors.end();
  } else if (pair[0] == "pid") {
    // pid (Passport ID) - a nine-digit number, including leading zeroes.
    const std::regex pid_regex("[0-9]{9}");
    return std::regex_match(pair[1], pid_regex);
  } else if (pair[0] == "cid") {
    // cid (Country ID) - ignored, missing or not.
    return false;
  } else {
    return false;
  }
}

bool fieldsValid(std::vector<std::string> elements) {
  int count = 0;

  for (size_t i = 0; i < elements.size(); i++) {
    std::cout << "element #" << i << ": " << elements[i] << "\n";
    if (elements[i].length() == 0) { continue; }

    auto keyValuePair = tokenize(elements[i], ':');

    std::cout << "    " << keyValuePair[0] << " -> " << keyValuePair[1] << ": ";
    if (fieldValid(keyValuePair)) {
      std::cout << "O\n";
      count++;
    } else {
      std::cout << "X\n";
    }
  }

  return count >= 7;
}

bool validatePassport(std::string entry) {
  auto elements = tokenize(entry, ' ');

  std::cout << "------------------------\n";
  // for(size_t i = 0; i < elements.size(); i++) {
    // std::cout << "  " << elements[i] << '\n';
  // }

  return fieldsValid(elements);
}

int countValidPassports(std::vector<std::string> passports) {
  int result = 0;

  for (size_t i = 0; i < passports.size(); i++) {
    if (validatePassport(passports[i])) {
      std::cout << "  [VALID]\n";
      result++;
    } else {
      std::cout << "  [invalid]\n";
    }
  }

  return result;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "Missing input file argument.\n";
    return 1;
  }

  std::vector<std::string> passports = readFile(argv[1]);

  int result = countValidPassports(passports);
  std::cout << "Number of valid passports: " << result << "\n";

  return 0;
}
