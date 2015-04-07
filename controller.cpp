#include "controller.h"
#include <map>

using namespace std;

Controller::Controller() {
    model = new Model();
    view = new View("Game", 1024, 768);
}

Controller::~Controller() {
    delete model;
    delete view;
}
/**
References:
https://wiki.libsdl.org/SDL_PollEvent
https://wiki.libsdl.org/SDL_Event
*/
void Controller::loop() {
    SDL_Event e;
    unsigned int lastTime = 0, currentTime;
    std::map<SDL_Keycode, Direction> direction;
    direction[SDLK_UP] = UP;
    direction[SDLK_DOWN] = DOWN;
    direction[SDLK_LEFT] = LEFT;
    direction[SDLK_RIGHT] = RIGHT;
    
    std::map<SDL_Keycode, char> text;
    text[SDLK_a] = 'a';
    text[SDLK_b] = 'b';
    text[SDLK_c] = 'c';
    text[SDLK_d] = 'd';
    text[SDLK_e] = 'a';
    text[SDLK_f] = 'a';
    text[SDLK_g] = 'a';
    text[SDLK_h] = 'a';
    text[SDLK_i] = 'a';
    text[SDLK_j] = 'a';
    text[SDLK_k] = 'a';
    text[SDLK_l] = 'a';
    text[SDLK_m] = 'a';
    text[SDLK_n] = 'a';
    text[SDLK_o] = 'a';
    text[SDLK_p] = 'a';
    text[SDLK_q] = 'a';
    text[SDLK_a] = 'a';
    text[SDLK_a] = 'a';
    

    string textEntry = "";
    while(!model->gameOver()) {
        currentTime = SDL_GetTicks();
        // Do stuff here to animate as necessary
        view->show(model);
        if (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
            case SDL_QUIT:
                return;
            case SDL_KEYDOWN:
                switch(e.key.keysym.sym) {
                case SDLK_DOWN:
                case SDLK_UP:
                case SDLK_LEFT:
                case SDLK_RIGHT:
//                    model->go(direction[e.key.keysym.sym]);
                break;
                default:
                        // the user pressed enter
                        if (e.key.keysym.sym == SDLK_RETURN) {
                            // send textEntry to the model
//                            model->doSomethingWith(textEntry);
                        } else {
                            textEntry = textEntry + text[e.key.keysym.sym];
                            // if you want, pass the word as you type it in...
                        }
                break;
                }
            case SDL_MOUSEBUTTONDOWN:
                break;
            }
        }
    }
    // TODO: show something nice?
    view->show(model);
    SDL_Delay(3000);
}
