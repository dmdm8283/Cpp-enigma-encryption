#include "keys.h"

Keys::Keys(int windowWidth) : keypressed('\0'){
    std::vector<string> layout = { "QWERTYUIOP", "ASDFGHJKL", "ZXCVBNM" };
    const int numKeys = 26;
    const int keyWidth = 70;
    const int keyHeight = 70;
    const int hGap = 10;
    const int vGap = 20;
    int startY = 50;

    for (size_t row = 0; row < layout.size(); row++) {
        const string& keysRow = layout[row];
        int numKeys = keysRow.size();

        int rowWidth = numKeys * keyWidth + (numKeys - 1) * hGap;
        int startX = (windowWidth - rowWidth) / 2;

        for (int i = 0; i < numKeys; i++) {
            VirtualKey vk;
            vk.label = keysRow[i];
            vk.keycode = SDL_Keycode(std::tolower(vk.label));
            vk.rect = { startX + i * (keyWidth + hGap), startY, keyWidth, keyHeight };
            vk.pressed = false;
            keys.push_back(vk);
        }
        startY += keyHeight + vGap;
    }
}
void Keys::input(const SDL_Event& input) {
    if (input.type == SDL_KEYDOWN) {
        SDL_Keycode code = input.key.keysym.sym;
        for (auto &key : keys) {
            if (key.keycode == code) {
                key.pressed = true;
                keypressed = key.label;
            }
        }
    }
    else if (input.type == SDL_KEYUP) {
        SDL_Keycode code = input.key.keysym.sym;
        for (auto &key : keys) {
            if (key.keycode == code) {
                key.pressed = false;
                keypressed = '\0';
            }
        }
    }
}
void Keys::render(SDL_Renderer* renderer) {
    for (const auto &key : keys) {
        if (key.pressed) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        }
        SDL_RenderFillRect(renderer, &key.rect);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &key.rect);
    }
}