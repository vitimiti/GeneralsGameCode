#ifndef SDL_MAIN_USE_CALLBACKS
    #define SDL_MAIN_USE_CALLBACKS
#endif // SDL_MAIN_USE_CALLBACKS

#include <iostream>
#include <print>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "defines.hpp"
#include "generated.hpp"

namespace {} // anonymous namespace

auto SDL_AppInit([[maybe_unused]] void** appstate, [[maybe_unused]] int argc,
                 [[maybe_unused]] char** argv) -> SDL_AppResult {
#ifdef GENERALS_AND_ZERO_HOUR_DEBUG
    SDL_SetLogPriorities(SDL_LOG_PRIORITY_VERBOSE);
#endif // GENERALS_AND_ZERO_HOUR_DEBUG

    SDL_SetAppMetadata("C&C Generals", GENERALS_VERSION_STRING, "generals.cnc");

    if (!SDL_InitSubSystem(SDL_INIT_VIDEO)) {
        std::println("Failed to initialize SDL3: {}", SDL_GetError()); // Make a logging class
    }

    return SDL_APP_CONTINUE;
}

auto SDL_AppIterate([[maybe_unused]] void* appstate) -> SDL_AppResult { return SDL_APP_CONTINUE; }

auto SDL_AppEvent([[maybe_unused]] void* appstate, [[maybe_unused]] SDL_Event* event)
    -> SDL_AppResult {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }

    return SDL_APP_CONTINUE;
}

auto SDL_AppQuit([[maybe_unused]] void* appstate, [[maybe_unused]] SDL_AppResult result) -> void {
    SDL_Quit();
}
