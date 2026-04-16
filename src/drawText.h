#ifndef DRAWTEXT_H
#define DRAWTEXT_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <vector>

extern TTF_Font *font;
extern SDL_FRect rect;
extern SDL_Renderer *renderer;
extern SDL_Texture *texture;
extern std::vector<SDL_Texture*> textures;

extern unsigned char tiny_ttf[];
extern unsigned int tiny_ttf_len;

bool initText();

extern int tileSizePixels; 
extern int tilesOffset;

void drawText(SDL_Renderer *renderer, int targetX, int targetY, int textureIndex);

#endif // DRAWTEXT_H