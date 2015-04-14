#include "view.h"

using namespace std;

// Initialize SDL
View::View(string title, int width, int height) {
    fail = false;
    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0) {
        fail = true;
        return;
    }
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fail = true;
        return;
    }
    // Get the screen
    screen = SDL_GetWindowSurface(window);
    //Initialize JPEG and PNG loading
    if( !( IMG_Init( IMG_INIT_JPG|IMG_INIT_PNG ) & (IMG_INIT_JPG|IMG_INIT_PNG) ) ) {
        fail = true;
        return;
    }
    //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
        fail = true;
        return;
    }

    // Initialize True type fonts
    if( TTF_Init() == -1 ) {
        return;
    }
    // Load assets
//    snake = load("assets/snake.png");
//    music = Mix_LoadMUS("assets/2Inventions_-_Johaness_Gilther_-_Don_t_leave_me.mp3");
//    if (music != NULL) {
//       Mix_PlayMusic( music, -1 );
//    }
//    food = Mix_LoadWAV("assets/yummy.wav");
    font = TTF_OpenFont( "assets/LiberationSans-Regular.ttf", 28 );

}

View::~View() {
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

/**
 *  Load an image from a file to a SDL_Surface
 */
SDL_Surface* View::load(char * path) {
    // Load image
    SDL_Surface* optimizedSurface = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path );
    if( loadedSurface == NULL ) {
        return NULL;
    }
    // Convert surface to screen format
    optimizedSurface = SDL_ConvertSurface( loadedSurface, screen->format, 0 );
    
    // Get rid of old loaded surface
    SDL_FreeSurface( loadedSurface );
    
    return optimizedSurface;
}

void View::show(Model * model) {

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,
        0x00, 0x00, 0x00));

    SDL_Color textColor = { 255, 255, 255 };
    
    SDL_Rect buttons[5];
    string labels[5] = {"", "Category", "Word", "Foo", "Bar"};
    
    for (int i = 0; i < 5; i++) {
        buttons[i].x = 120*i;
        buttons[i].y = 100;
        buttons[i].w = 100;
        buttons[i].h = 30;
        SDL_FillRect(screen, &buttons[i], SDL_MapRGB(screen->format,
                                              0x00, 0xff, 0x00));
        text = TTF_RenderText_Solid( font, labels[i].c_str(), textColor );
        SDL_BlitSurface( text, NULL, screen, &buttons[i] );
        SDL_FreeSurface(text);
    }

    SDL_Rect dest;
    dest.y = 30;
    // Instead of doing a query here
    // Get the current result set from the model.
    // the controller should tell the model what result set to show and populate model->resultList
    text = TTF_RenderText_Solid( font, model->getText().c_str(), textColor );
    dest.x = 10;
    dest.y += 30;
    SDL_BlitSurface( text, NULL, screen, &dest );
    SDL_FreeSurface(text);

    for (int i = 0; i < model->result.size(); i++) {
        text = TTF_RenderText_Solid( font, model->result[i].c_str(), textColor );
        dest.x = 10;
        dest.y += 30;
        SDL_BlitSurface( text, NULL, screen, &dest );
    }
    // Probably call SDL_FillRect or SDL_BlitSurface a bunch here :-)

    SDL_UpdateWindowSurface(window);
}
