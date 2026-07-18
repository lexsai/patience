#include <Windows.h>

#include "renderer/renderer.hpp"
#include "game/game.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <glad/glad.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

namespace {
  void receiveInput(UserCommand& userCommand, SDL_Scancode keyCode, bool isDown) {
    switch (keyCode) {
      case SDL_SCANCODE_W: {
        userCommand.forward = isDown;
      } break;

      case SDL_SCANCODE_S: {
        userCommand.back = isDown;
      } break;
      
      case SDL_SCANCODE_A: {
        userCommand.left = isDown;
      } break;

      case SDL_SCANCODE_D: {
        userCommand.right = isDown;
      } break;
    }
  }
};

int main(int argc, char** argv) {
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
    SDL_Log("Failure!");
    return -1;
  } 
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  SDL_Window *window = SDL_CreateWindow("test", 640, 480, SDL_WINDOW_OPENGL);
  if (!window) {
    SDL_Log("SDL Error: %s\n", SDL_GetError());
    SDL_Quit();
    return EXIT_FAILURE;
  }

  SDL_GLContext glContext = SDL_GL_CreateContext(window);
  if (!glContext) {
    SDL_Log("SDL Error: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_FAILURE;
  }

  Game game{};
  game.init();

  Renderer renderer{ 10000 };
  renderer.init();

  UserCommand userCommand{};

  bool running = true;
  while (running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_EVENT_QUIT: {
          running = false;
        } break;
        case SDL_EVENT_KEY_DOWN: {
          receiveInput(userCommand, event.key.scancode, true);
        } break;
        case SDL_EVENT_KEY_UP: {
          receiveInput(userCommand, event.key.scancode, false);
        } break;
      }
    }

    game.update(renderer, userCommand);

    SDL_GL_SwapWindow(window);
  }

  SDL_DestroyWindow(window);
  SDL_GL_DestroyContext(glContext);
  SDL_Quit();
  return EXIT_SUCCESS;
}
