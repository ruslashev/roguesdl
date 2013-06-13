#ifndef MAIN_HPP
#define MAIN_HPP

SDL_Texture* LoadImage(const char* imagePath, SDL_Renderer **rend);
void ApplySurface(int x, int y, SDL_Texture *tex, SDL_Renderer *rend);

#endif
