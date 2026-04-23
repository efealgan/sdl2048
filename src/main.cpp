#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_scancode.h>
#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "drawText.h"
#include "game.h"

static SDL_Window *window = NULL;
SDL_Renderer *renderer =    NULL;
SDL_Texture *texture =      NULL;

extern unsigned char tiny_ttf[];
extern unsigned int tiny_ttf_len;

int boardSize = 4;

int tileSizePixels = 100; 
int tilesOffset = 10;
int dimensions = boardSize;
int windowDimensions = dimensions*(tilesOffset+tileSizePixels) + tilesOffset;

bool gameRunning = true;


SDL_AppResult handleKeyEvents(SDL_Scancode scancode){

    Direction direction = None;

    switch(scancode){
        case SDL_SCANCODE_UP:
        case SDL_SCANCODE_W:
            SDL_Log("Pressed UP");
            direction = Up;
            break;
        case SDL_SCANCODE_LEFT:
        case SDL_SCANCODE_A:
            SDL_Log("Pressed LEFT");
            direction = Left;
            break;
        case SDL_SCANCODE_DOWN:
        case SDL_SCANCODE_S:
            SDL_Log("Pressed DOWN");
            direction = Down;
            break;
        case SDL_SCANCODE_RIGHT:
        case SDL_SCANCODE_D:
            SDL_Log("Pressed RIGHT");
            direction = Right;
            break;
        default:
            break;
        
    }

    if (direction != None) {        //actually pressed a direction key
        if(!moveBoard(direction)){  //board actually moved
            spawnTile();
        }
    }

    return SDL_APP_CONTINUE;
}

//runs once at startup
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]){
    SDL_SetAppMetadata("2048", "0.1", "com.2048.efeAlgan");


    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    if (!SDL_CreateWindowAndRenderer("2048", windowDimensions, windowDimensions, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!TTF_Init()) {
        SDL_Log("Couldn't initialise SDL_ttf: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (initText()){
        SDL_Log("Couldn't initialise text: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }


    SDL_SetRenderLogicalPresentation(renderer, windowDimensions, windowDimensions, SDL_LOGICAL_PRESENTATION_LETTERBOX);


    ///Actual Game initialization:
    initGame();
    spawnTile();
    spawnTile();

    

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

//events go to this function.
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event){
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }

    else if (event->type == SDL_EVENT_KEY_DOWN) {
        return handleKeyEvents(event->key.scancode);
    }

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}


//runs every frame.
SDL_AppResult SDL_AppIterate(void *appstate){
    const double now = ((double)SDL_GetTicks()) / 10000.0;  /* convert from milliseconds to seconds. */
    /* choose the color for the frame we will draw. The sine wave trick makes it fade between colors smoothly. */
    const float red = (float) (0.5 + 0.5 * SDL_sin(now));
    const float green = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
    const float blue = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));
    SDL_SetRenderDrawColorFloat(renderer, red/4, green/4, blue/4, SDL_ALPHA_OPAQUE_FLOAT);  /* new color, full alpha. */

    /* clear the window to the draw color. */
    SDL_RenderClear(renderer);

    //^Draws the colors in the background.
    //-------------
    //v I want to draw a grey foreground here.
    
    SDL_FRect rect;
    //top left of screen is 0,0.
    //so the rectangle will be offset 10 pixels away from the corner, in each direction.
    
    rect.x = rect.y = tilesOffset;
    rect.w = rect.h = tileSizePixels;


    
    for (int i = 0; i < dimensions; i++) {
        for (int j = 0; j < dimensions; j++) {
            switch (board.at(i).at(j)) {
                case 0:
                    SDL_SetRenderDrawColor(renderer, 100, 100, 100, SDL_ALPHA_OPAQUE);
                    SDL_RenderFillRect(renderer, &rect);
                    break;
                case 1:
                    SDL_SetRenderDrawColor(renderer, 238, 228, 218, SDL_ALPHA_OPAQUE);
                    SDL_RenderFillRect(renderer, &rect);
                    break;
                case 2:
                    SDL_SetRenderDrawColor(renderer, 237, 224, 200, SDL_ALPHA_OPAQUE);
                    SDL_RenderFillRect(renderer, &rect);
                    break;
                case 3:
                    SDL_SetRenderDrawColor(renderer, 242, 177, 121, SDL_ALPHA_OPAQUE);
                    SDL_RenderFillRect(renderer, &rect);
                    break;
                case 4:
                    SDL_SetRenderDrawColor(renderer, 245, 149, 99, SDL_ALPHA_OPAQUE);
                    break;
                case 5:
                    SDL_SetRenderDrawColor(renderer, 246, 124, 95, SDL_ALPHA_OPAQUE);
                    break;
                case 6:
                    SDL_SetRenderDrawColor(renderer, 246, 94, 59, SDL_ALPHA_OPAQUE);
                    break;
                case 7:
                    SDL_SetRenderDrawColor(renderer, 237, 207, 114, SDL_ALPHA_OPAQUE);
                    break;
                case 8:
                    SDL_SetRenderDrawColor(renderer, 237, 204, 97, SDL_ALPHA_OPAQUE);
                    break;
                case 9:
                    SDL_SetRenderDrawColor(renderer, 237, 204, 97, SDL_ALPHA_OPAQUE);
                    break;
                case 10:
                    SDL_SetRenderDrawColor(renderer, 237, 197, 63, SDL_ALPHA_OPAQUE);
                    break;
                case 11:
                    SDL_SetRenderDrawColor(renderer, 237, 194, 46, SDL_ALPHA_OPAQUE);
                    break;
                default:
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                    break;
            }

            SDL_RenderFillRect(renderer, &rect);
            if (board.at(i).at(j)) {
                drawText(renderer, rect.x, rect.y, board.at(i).at(j) - 1);
            }
            rect.x += tileSizePixels+tilesOffset;
        }
        rect.x = tilesOffset;
        rect.y += tileSizePixels+tilesOffset;
    }

    /* put the newly-cleared rendering on the screen. */
    SDL_RenderPresent(renderer);



    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

//handles shutdown
void SDL_AppQuit(void *appstate, SDL_AppResult result){
    /* SDL will clean up the window/renderer for us. */
}
