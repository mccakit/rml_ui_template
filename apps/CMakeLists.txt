if(ANDROID)
    add_library(main SHARED main.cpp)
else()
    add_executable(main main.cpp)
endif()
target_compile_definitions(main PUBLIC SDL_MAIN_USE_CALLBACKS)
set_property(TARGET main PROPERTY WIN32_EXECUTABLE TRUE)
if(EMSCRIPTEN)
    target_link_options(main PRIVATE "-sASYNCIFY=1")
    target_link_libraries(
        main
        PRIVATE
            "--preload-file ${CMAKE_CURRENT_LIST_DIR}/demo.rml@/"
            "--preload-file ${CMAKE_CURRENT_LIST_DIR}/invader.rcss@/"
            "--preload-file ${CMAKE_CURRENT_LIST_DIR}/invader.tga@/"
            "--preload-file ${CMAKE_CURRENT_LIST_DIR}/LatoLatin-Bold.ttf@/"
            "--preload-file ${CMAKE_CURRENT_LIST_DIR}/LatoLatin-BoldItalic.ttf@/"
            "--preload-file ${CMAKE_CURRENT_LIST_DIR}/LatoLatin-Italic.ttf@/"
            "--preload-file ${CMAKE_CURRENT_LIST_DIR}/LatoLatin-Regular.ttf@/"
            "--preload-file ${CMAKE_CURRENT_LIST_DIR}/rml.rcss@/"
            "--preload-file ${CMAKE_CURRENT_LIST_DIR}/window.rml@/"
    )
endif()
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
    if(ANDROID)
        set(outname ${CMAKE_SOURCE_DIR}/gradle/app/src/main/assets)
    else()
        set(outname ${CMAKE_BINARY_DIR}/apps)
    endif()
    add_custom_command(
        TARGET main
        POST_BUILD
        COMMAND
            ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_LIST_DIR}/${filename}" "${outname}"
    )
endmacro()
macro(copy_directory_helper foldername)
    if(ANDROID)
        set(outdir ${CMAKE_SOURCE_DIR}/gradle/app/src/main/assets)
    else()
        set(outdir ${CMAKE_BINARY_DIR}/apps)
    endif()
    add_custom_command(
        TARGET main
        POST_BUILD
        COMMAND
            ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_LIST_DIR}/${foldername}" "${outdir}/${foldername}"
    )
endmacro()
if(NOT EMSCRIPTEN)
    copy_helper("demo.rml")
    copy_helper("invader.rcss")
    copy_helper("invader.tga")
    copy_helper("LatoLatin-Bold.ttf")
    copy_helper("LatoLatin-BoldItalic.ttf")
    copy_helper("LatoLatin-Italic.ttf")
    copy_helper("LatoLatin-Regular.ttf")
    copy_helper("rml.rcss")
    copy_helper("window.rml")
endif()
