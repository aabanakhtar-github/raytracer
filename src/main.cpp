#include "Renderer.h"
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

  SDL_Delay(5000);

  SDL_Quit();
  std::cout << "test";
  return 0;
}
