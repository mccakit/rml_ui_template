add_subdirectory(sdl)

set(SDLTTF_VENDORED ON)
add_subdirectory(sdl_ttf)

set(SDLMIXER_VENDORED ON)
set(SDLMIXER_MIDI_NATIVE OFF)
set(SDLMIXER_WAVPACK OFF)
add_subdirectory(sdl_mixer)

set(SDLIMAGE_VENDORED ON)
set(SDLIMAGE_AVIF OFF)
add_subdirectory(sdl_image)

set(RMLUI_BACKEND SDL_GL3)
add_subdirectory(rml_ui)
set(RMLUI_BACKEND_PATH rml_ui/Backends)
add_library(rmlui_backend_SDL_GL3 INTERFACE)
target_compile_definitions(
    rmlui_backend_SDL_GL3
    INTERFACE RMLUI_SDL_VERSION_MAJOR=3
)
target_sources(
    rmlui_backend_SDL_GL3
    INTERFACE
        ${RMLUI_BACKEND_PATH}/RmlUi_Platform_SDL.cpp
        ${RMLUI_BACKEND_PATH}/RmlUi_Renderer_GL3.cpp
        ${RMLUI_BACKEND_PATH}/RmlUi_Backend_SDL_GL3.cpp
)
target_include_directories(
    rmlui_backend_SDL_GL3
    INTERFACE ${RMLUI_BACKEND_PATH}
)
if(EMSCRIPTEN)
    target_link_options(rmlui_backend_SDL_GL3 INTERFACE "-sUSE_WEBGL2=1")
elseif(ANDROID)
    target_link_libraries(rmlui_backend_SDL_GL3 INTERFACE GLESv3)
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(rmlui_backend_SDL_GL3 INTERFACE OpenGL::GL)
endif()
