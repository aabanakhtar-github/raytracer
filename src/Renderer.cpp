#include "Renderer.h"
#include "SDL3/SDL_render.h"
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
}

auto Renderer::putPixel(int x, int y, const Color &color) -> void {
  if (!getValid())
    return;
  auto r = std::min(255U, static_cast<unsigned int>(color.R * 255));
  auto g = std::min(255U, static_cast<unsigned int>(color.G * 255));
  auto b = std::min(255U, static_cast<unsigned int>(color.B * 255));
  auto a = std::min(255U, static_cast<unsigned int>(color.A * 255));
  std::uint8_t pr, pg, pb, pa;
  SDL_GetRenderDrawColor(renderer_, &pr, &pg, &pb, &pa);
  SDL_SetRenderDrawColor(renderer_, (int)r, (int)g, (int)b, (int)a);
  SDL_RenderPoint(renderer_, x, y);
  SDL_SetRenderDrawColor(renderer_, pr, pg, pb, pa);
}

Renderer::~Renderer() {
  if (renderer_ != nullptr) {
    SDL_DestroyRenderer(renderer_);
  }
  if (window_ != nullptr) {
    SDL_DestroyWindow(window_);
  }
  renderer_ = nullptr;
  window_ = nullptr;
  valid_ = false;
}
