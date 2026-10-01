#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

class ReadFile {
  std::filesystem::path filePath;

public:
  explicit ReadFile(std::filesystem::path path) : filePath(std::move(path)) {}

  // Option 1: Read the file line by line
  std::vector<std::string> readByLine() const {
    std::vector<std::string> lines;
    std::ifstream file(filePath);

    if (!file.is_open()) {
      return lines; // Returns empty vector if file fails to open
    }

    std::string line;
    while (std::getline(file, line)) {
      lines.push_back(line);
    }

    return lines;
  }

  // Option 2: Read the file word by word (whitespace-delimited)
  std::vector<std::string> readByWord() const {
    std::vector<std::string> words;
    std::ifstream file(filePath);

    if (!file.is_open()) {
      return words;
    }

    std::string word;
    while (file >> word) { // Automatically splits by spaces, tabs, and newlines
      words.push_back(word);
    }

    return words;
  }

};
