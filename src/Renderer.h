#ifndef RENDERER_H
#define RENDERER_H

#include "Color.h"
#include "SDL3/SDL.h"
#include <iostream>

class Renderer {
public:
  Renderer();
  ~Renderer();
  auto putPixel(int x, int y, const Color &color) -> void;
  auto getValid() -> bool { return valid_; }
  auto clear() -> void {
    if (!getValid())
      std::cout << "hi";
    SDL_RenderPresent(renderer_);
    SDL_RenderClear(renderer_);
  }

private:
  bool valid_ = false;
  SDL_Window *window_;
  SDL_Renderer *renderer_;
};

#endif // RENDERER_H
