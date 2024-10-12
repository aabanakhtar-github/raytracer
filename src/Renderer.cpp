#include "Renderer.h"
#include <iostream>

Renderer::Renderer() {
  window_ = SDL_CreateWindow("raytracer", 900, 600, 0);
  if (window_ == nullptr) {
    std::cerr << "Cannot create window! " << SDL_GetError() << "\n";
    return;
  }
  // second arg is render driver lol
  renderer_ = SDL_CreateRenderer(window_, nullptr);
  if (renderer_ == nullptr) {
    std::cerr << "Cannot create renderer! " << SDL_GetError() << "\n";
    return;
  }
  valid_ = true;

  bool running = true;
  SDL_Event event;
  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        running = false;
      }
    }

    SDL_RenderClear(renderer_);
    // Add your rendering logic here

    SDL_RenderPresent(renderer_);
  }

  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
  SDL_Quit();
}
