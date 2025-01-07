#include "Camera.h"
#include "Hittable.h"
#include "Renderer.h"
#include "SDL3/SDL_events.h"
#include "Vector3.h"
#include <initializer_list>
#include <iostream>
#include <memory>

auto createWorld() -> HittableList {
  auto l = HittableList::ListType{
      std::static_pointer_cast<Hittable>(
          std::make_shared<Sphere>(0.5, Math::Point3{0, 0, 1.0})),
      std::static_pointer_cast<Hittable>(
          std::make_shared<Sphere>(100, Math::Point3{0, -100.5, -1}))};
  return {l};
}

auto main(int argc, char *argv[]) -> int {
  auto world = createWorld();
  auto camera = Camera{};

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    std::cerr << "Could not initalize SDL3!";
    return -1;
  }
  auto renderer = Renderer{};
  if (!renderer.getValid()) {
    std::cerr << "Failed to create a raytracing context!\n";
    return 1;
  }
  auto e = SDL_Event{};
  auto quit = false;
  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_EVENT_QUIT) {
        quit = true;
      }
    }
    camera.doRaytrace(renderer, world);
    renderer.clear();
  }

  SDL_Quit();
  std::cout << "test";
  return 0;
}
