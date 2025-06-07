add_executable(main main.cpp)
target_link_libraries(
    main
    PRIVATE
        SDL3_ttf::SDL3_ttf
        SDL3_mixer::SDL3_mixer
        SDL3_image::SDL3_image
        SDL3::SDL3
        RmlUi::RmlUi
        rmlui_backend_SDL_GL3
)
