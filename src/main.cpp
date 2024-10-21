#include "Renderer.h"
#include "SDL3/SDL_events.h"
#include <iostream>

auto main(int argc, char *argv[]) -> int {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    std::cerr << "Could not initalize SDL3!";
    return -1;
  }

  Renderer renderer;
  if (!renderer.getValid()) {
    std::cerr << "Failed to create a raytracing context!\n";
    return 1;
  }

  SDL_Event e;

  bool quit = false;
  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_EVENT_QUIT) {
        quit = true;
      }
    }
    renderer.putPixel(100, 100, {1.0, 1.0, 1.0, 1.0});
    for (int i = 0; i < 900; ++i) {
      renderer.putPixel(50, i, {1.0, 0.0, 1.0, 1.0});
    }
    renderer.clear();
  }

  SDL_Quit();
  std::cout << "test";
  return 0;
}
