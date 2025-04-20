/*by dmdm
 *enigma encryption
 *winter/spring 2024-2025
 *using Simple DirectMedia Layer for keyboard display
 *and clion ide
 */
/*
 *format for rotors.txt:
EKMFLGDQVZNTOWYHXUSPAIBRCJ\n
 *
 */


#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <cctype>
#include <fstream>
#include <iomanip>
#include "keys.h"
#include "rotors.h"

int main(int argc, char* argv[]) {
    const int windowWidth = 800;
    const int windowHeight = 400;

     if (SDL_Init(SDL_INIT_VIDEO) != 0) {
         std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
         return 1;
    }


    SDL_Window *window = SDL_CreateWindow("Virtual Keyboard",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          800, 300,
                                          SDL_WINDOW_SHOWN);
    if (!window) {
         std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
         SDL_Quit();
         return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
         std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
         SDL_DestroyWindow(window);
         SDL_Quit();
         return 1;
    }



     Keys virtualKeyBoard(windowWidth);
     vector <rotors> encrypt;
     bool quit = false;
     bool keyProcessed = false;
     SDL_Event input;

     ofstream outFile("output.txt");
     if (!outFile) {cerr << "output file error" << endl; }
     outFile << std::unitbuf;


     while (!quit) {
          while (SDL_PollEvent(&input)) {
               if (input.type == SDL_QUIT || input.key.keysym.sym == SDLK_ESCAPE) {
                    quit = true;
                    break;
               }
               virtualKeyBoard.input(input);
               if (input.type == SDL_KEYDOWN && !keyProcessed) {
                    SDL_Keycode code = input.key.keysym.sym;
                    char keyChar = static_cast<char>(code);
                    if (input.key.keysym.sym == SDLK_SPACE) {
                         outFile << " ";
                         cout << "space" << endl;
                    } else if (input.key.keysym.sym == SDLK_RETURN) {
                         outFile << endl;
                         cout << "endl" << endl;
                    } else if (isalpha(keyChar)) {
                         encrypt.push_back(rotors(keyChar));
                         char encryptedChar = encrypt.back().encrypt();
                         cout << keyChar << " -> " << encryptedChar << endl;
                         outFile << encryptedChar;
                         outFile.flush();
                         keyProcessed = true;
                    }
               }
               else if (input.type == SDL_KEYUP) {
                    keyProcessed = false;
               }

          }
          SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
          SDL_RenderClear(renderer);

          virtualKeyBoard.render(renderer);
          SDL_RenderPresent(renderer);
          SDL_Delay(16);
     }



    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
