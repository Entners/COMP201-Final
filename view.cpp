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

void View::drawText(string str, int x, int y) {
    SDL_Rect dest;
    SDL_Color textColor = { 255, 255, 255 };
    text = TTF_RenderText_Solid( font, str.c_str(), textColor );
    dest.x = x;
    dest.y = y;
    SDL_BlitSurface( text, NULL, screen, &dest );
    SDL_FreeSurface(text);
}

void View::show(Model * model) {

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,
        0x00, 0x00, 0x00));

    
    SDL_Rect buttons[5];
    string labels[] = {"Clear", "Search by Word", "Search by Category", "Add", "Remove"};
    
    // Draw buttons and labels
    for (int i = 0; i < 5; i++) {
        buttons[i].x = 120*i;
        buttons[i].y = 100;
        buttons[i].w = 110;
        buttons[i].h = 30;
        SDL_FillRect(screen, &buttons[i], SDL_MapRGB(screen->format,
                                              0x00, 0xff, 0x00));
        drawText(labels[i], buttons[i].x, buttons[i].y);
    }
    
    SDL_Rect dest;
    dest.x = 300;
    dest.y = 30;
    dest.w = 300;
    dest.h = 30;
    
    // Show the word text entry field
    if (model->operation != CLEAR ) {
        SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format,
                                                     0xcc, 0xcc, 0xcc));
        // draw a box around here (perhaps a box within a box using fillrect
        drawText("Enter word:", 100, 30);
        drawText(model->word, dest.x, dest.y);
    }
    
    int y = 60;
    // Show result set
    switch (model->operation) {
        case SEARCH_BY_WORD: case SEARCH_BY_CATEGORY:
            for (int i = 0; i < model->result.size(); i++) {
                drawText(model->result[i].word, 10, y);
                drawText(model->result[i].category, 200, y);
                y += 30;
            }
            break;
        case ADD:
            break;
        case REMOVE:
            break;
        case CLEAR: default:
            break;
    }

    SDL_UpdateWindowSurface(window);
}
