add_subdirectory(sdl)
set(SDLTTF_VENDORED ON)
add_subdirectory(sdl_ttf)

set(SDLMIXER_VENDORED ON)
set(SDLMIXER_MIDI_NATIVE OFF)
set(SDLMIXER_GME OFF)
set(SDLMIXER_WAVPACK OFF)
set(SDLMIXER_MOD OFF)
set(SDLMIXER_OPUS OFF)
add_subdirectory(sdl_mixer)

set(SDLIMAGE_VENDORED ON)
set(SDLIMAGE_AVIF OFF)
set(SDLIMAGE_BMP OFF)
set(SDLIMAGE_JPEG OFF)
set(SDLIMAGE_WEBP OFF)
add_subdirectory(sdl_image)

add_subdirectory(rml_ui)
set(RMLUI_BACKEND_PATH rml_ui/Backends)
add_library(rmlui_backend_SDL_GL3 STATIC)
target_sources(
    rmlui_backend_SDL_GL3
    PRIVATE
        ${RMLUI_BACKEND_PATH}/RmlUi_Platform_SDL.cpp
        ${RMLUI_BACKEND_PATH}/RmlUi_Renderer_GL3.cpp
        ${RMLUI_BACKEND_PATH}/RmlUi_Backend_SDL_GL3.cpp
)
target_include_directories(rmlui_backend_SDL_GL3 PUBLIC ${RMLUI_BACKEND_PATH})
target_compile_definitions(
    rmlui_backend_SDL_GL3
    PRIVATE RMLUI_SDL_VERSION_MAJOR=3 RMLUI_NUM_MSAA_SAMPLES=4
)
target_link_libraries(
    rmlui_backend_SDL_GL3
    PRIVATE SDL3::SDL3 SDL3_image::SDL3_image RmlUi::RmlUi
)
find_package(OpenGL REQUIRED)
target_link_libraries(rmlui_backend_SDL_GL3 PRIVATE OpenGL::GL)
