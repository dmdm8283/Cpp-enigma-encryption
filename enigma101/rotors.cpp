#include "rotors.h"

#include <fstream>
#include <iostream>
#include <vector>
std::vector<std::string> rotors::rotorMappings;
void rotors::loadFromFile(const std::string& filename) {
    if (!rotorMappings.empty())
        return;

    std::ifstream in(filename);
    if (!in) {
        std::cerr << "could not open file " << filename << "'\n";
        std::exit(1);
    }

    std::string line;
    while (std::getline(in, line)) {
        if (!line.empty() && (int)line.size() == MAX_SIZE)
            rotorMappings.push_back(line);
        else
            std::cerr << "skipping invalid rotor line " << line << "\n";
    }

    if (rotorMappings.empty()) {
        std::cerr << "no valid rotors\n";
        std::exit(1);
    }
}
rotors::rotors(char input) {
    loadFromFile("rotors.txt");

    char up = std::toupper(input);
    num = 0;
    while (num < MAX_SIZE && in[num] != up)
        num++;
    if (num == MAX_SIZE) {
        std::cerr << "invalid input char "<< input << "'\n";
        std::exit(1);
    }
}
int rotors::getNum() {
    return num;
}

char rotors::encrypt() {
    const auto& wiring = rotorMappings[ rotorCount % rotorMappings.size() ];
    char out = wiring[num];
    rotorCount++;
    return out;
}