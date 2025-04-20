#ifndef ROTORS_H
#define ROTORS_H
#define ROTORS_H
#include <cctype>
#include <vector>
#include <memory>
#include <string>
const int MAX_SIZE = 26;
inline int rotorCount = 0;

class rotors {
private:
    char in[MAX_SIZE+1] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int num;
    static std::vector<std::string> rotorMappings;

    static void loadFromFile(const std::string& filename);

public:
    rotors(char input);
    int getNum();
    char encrypt();


};

#endif //ROTORS_H
