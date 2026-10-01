#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

class ReadFile { // Renamed to PascalCase for standard C++ naming conventions
private:
    std::string path;
    std::vector<std::string> contents;
    bool validPath;

public: // 1. Added public access specifier so you can actually use the class
    
    // 2. Used the 'path' argument instead of hardcoding "example.txt"
    ReadFile(std::string filePath) : path(filePath), validPath(true) {
        std::ifstream file(path);
        
        if (!file.is_open()) {
            std::cerr << "Error: Could not open the file at " << path << std::endl;
            validPath = false;
            return; // 3. Stop execution early if file fails to open
        }
        
        std::string line;
        while (std::getline(file, line)) {
            contents.push_back(line);
        }
    }

    // 4. Added 'const' to prevent modifying class data while reading contents
    std::vector<std::string> getContent() const {
        if (!validPath) {
            return std::vector<std::string>{}; // Returns an empty vector if invalid
        }
        return contents;
    }

    // 5. Cleaned up the destructor
    ~ReadFile() {
        // 'std::ifstream' closes itself automatically when it goes out of scope 
        // inside the constructor. Destructors cannot return values.
    }
};
