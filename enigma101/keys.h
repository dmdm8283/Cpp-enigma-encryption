//
// Created by dmdm on 3/1/25.
//
#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include <vector>
#include <cctype>

#ifndef KEYS_H
#define KEYS_H
using namespace std;

class Keys{
public:
    char keypressed;
    Keys(int);
    void input(const SDL_Event& input);
    void render(SDL_Renderer* renderer);

private:
    struct VirtualKey {
        SDL_Keycode keycode;
        SDL_Rect rect;
        bool pressed;
        char label;
    };

    vector<VirtualKey> keys;
};


#endif //KEYS_H
