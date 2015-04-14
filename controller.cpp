#include "controller.h"
#include <map>
#include <iostream>

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
    text[SDLK_e] = 'e';
    text[SDLK_f] = 'f';
    text[SDLK_g] = 'g';
    text[SDLK_h] = 'h';
    text[SDLK_i] = 'i';
    text[SDLK_j] = 'j';
    text[SDLK_k] = 'k';
    text[SDLK_l] = 'l';
    text[SDLK_m] = 'm';
    text[SDLK_n] = 'n';
    text[SDLK_o] = 'o';
    text[SDLK_p] = 'p';
    text[SDLK_q] = 'q';
    text[SDLK_r] = 'r';
    text[SDLK_s] = 's';
    text[SDLK_t] = 't';
    text[SDLK_u] = 'u';
    text[SDLK_v] = 'v';
    text[SDLK_w] = 'w';
    text[SDLK_x] = 'x';
    text[SDLK_y] = 'y';
    text[SDLK_z] = 'z';

    string textEntry = "";
    SDL_Rect mouse;
    
    SDL_Rect buttons[5];
    
    for (int i = 0; i < 5; i++) {
        buttons[i].x = 120*i;
        buttons[i].y = 100;
        buttons[i].w = 100;
        buttons[i].h = 30;
    }
    
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
                            model->runQuery();
                        } else {
                            textEntry = textEntry + text[e.key.keysym.sym];
                            model->setText(textEntry);
                            // if you want, pass the word as you type it in...
                        }
                break;
                }
            case SDL_MOUSEBUTTONDOWN:
                    mouse.x = e.button.x;
                    mouse.y = e.button.y;
                    mouse.w = 1;
                    mouse.h = 1;
                    for (int i = 0; i < 5; i++) {
                        if (SDL_HasIntersection(&buttons[i], &mouse)) {
                            cout << "got here" << endl;
                            model->setEntry((Entry)i);
                        }
                    }
                break;
            }
        }
    }
    // TODO: show something nice?
    view->show(model);
    SDL_Delay(3000);
}
