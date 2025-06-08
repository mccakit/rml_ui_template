add_executable(main main.cpp)
target_compile_definitions(main PUBLIC SDL_MAIN_USE_CALLBACKS)
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
macro(copy_helper filename)
    set(outname ${CMAKE_BINARY_DIR}/apps)
    add_custom_command(
        TARGET main
        POST_BUILD
        COMMAND
            ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_LIST_DIR}/${filename}" "${outname}"
    )
endmacro()
copy_helper("demo.rml")
copy_helper("invader.rcss")
copy_helper("invader.tga")
copy_helper("LatoLatin-Bold.ttf")
copy_helper("LatoLatin-BoldItalic.ttf")
copy_helper("LatoLatin-Italic.ttf")
copy_helper("LatoLatin-Regular.ttf")
copy_helper("rml.rcss")
copy_helper("window.rml")
