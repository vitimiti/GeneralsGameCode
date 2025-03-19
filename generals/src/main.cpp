#ifndef SDL_MAIN_USE_CALLBACKS
    #define SDL_MAIN_USE_CALLBACKS
#endif // SDL_MAIN_USE_CALLBACKS

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <print>
#include <vector>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "defines.hpp"
#include "generated.hpp"

namespace {
constexpr std::int32_t default_window_width  = 800;
constexpr std::int32_t default_window_height = 600;

struct state_t {
    SDL_Window* window = nullptr;
};

struct command_line_options_t {
    bool         windowed_mode_requested = false;
    std::int32_t requested_xres          = default_window_width;
    std::int32_t requested_yres          = default_window_height;
};

auto process_command_line_arguments(int const argc, char** argv) -> command_line_options_t {
    std::vector<std::string> tokens(argc - 1);
    for (int i = 1; i < argc; ++i) {
        tokens.emplace_back(argv[i]);
    }

    auto         windowed_mode_requested = false;
    std::int32_t requested_xres          = default_window_width;
    std::int32_t requested_yres          = default_window_height;
    for (auto i = 0; i < tokens.size(); ++i) {
        // Into lower case
        std::ranges::transform(tokens[i].begin(), tokens[i].end(), tokens[i].begin(), ::tolower);

        // Windowed mode
        if (tokens[i] == "-win") {
            windowed_mode_requested = true;
        }

        // Width
        if (tokens[i] == "-xres") {
            requested_xres = std::stoi(tokens[++i]);
        }

        // Height
        if (tokens[i] == "-yres") {
            requested_yres = std::stoi(tokens[++i]);
        }
    }

    return {.windowed_mode_requested = windowed_mode_requested,
            .requested_xres          = requested_xres,
            .requested_yres          = requested_yres};
}
} // anonymous namespace

auto SDL_AppInit(void** appstate, [[maybe_unused]] int argc, [[maybe_unused]] char** argv)
    -> SDL_AppResult {
#ifdef GENERALS_AND_ZERO_HOUR_DEBUG
    SDL_SetLogPriorities(SDL_LOG_PRIORITY_VERBOSE);
#endif // GENERALS_AND_ZERO_HOUR_DEBUG

    SDL_SetAppMetadata("C&C Generals", GENERALS_VERSION_STRING, "generals.cnc");

    if (!SDL_InitSubSystem(SDL_INIT_VIDEO)) {
        std::println("Failed to initialize SDL3: {}", SDL_GetError()); // Make a logging class
    }

    auto const [windowed_mode_requested, requested_xres, requested_yres] =
        process_command_line_arguments(argc, argv);

    state_t         state{};
    SDL_WindowFlags window_flags = SDL_WINDOW_RESIZABLE;
    if (!windowed_mode_requested) {
        window_flags |= SDL_WINDOW_FULLSCREEN;
    }

    auto const actual_width  = requested_xres;
    auto const actual_height = requested_yres;
    state.window = SDL_CreateWindow("Command and Conquer - Generals", actual_width, actual_height,
                                    window_flags);

    *appstate = &state;
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
