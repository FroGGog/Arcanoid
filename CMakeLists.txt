cmake_minimum_required(VERSION 3.15)

project (Arcanoid LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)

set(SFML_BUILD_NETWORK FALSE) 
FetchContent_MakeAvailable(SFML)

set (SOURCE_FILES

    "src/code/Ball.cpp"
    "src/code/headers/Ball.h"

    "src/code/Bonuses.cpp"
    "src/code/headers/Bonuses.h"

    "src/code/Game.cpp"
    "src/code/headers/Game.h"

    "src/code/main.cpp"

    "src/code/Player.cpp"
    "src/code/headers/Player.h"

    "src/code/Targets.cpp"
    "src/code/headers/Targets.h"

)


add_executable(Arcanoid ${SOURCE_FILES})
target_link_libraries(Arcanoid PRIVATE sfml-graphics)
target_compile_features(Arcanoid PRIVATE cxx_std_17)

# add precompiled headers
target_precompile_headers(Arcanoid PRIVATE src/code/headers/stdafx.h)

# Copy assets
set (BUFFICONS

    "${CMAKE_SOURCE_DIR}/src/assets/bufficons/increaseLenght.png"
    "${CMAKE_SOURCE_DIR}/src/assets/bufficons/multiplyBall.png"
    "${CMAKE_SOURCE_DIR}/src/assets/bufficons/speedUp.png"

)

add_custom_command(TARGET Arcanoid POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:Arcanoid>/textures
)
 

foreach(BUFFICON ${BUFFICONS})

    add_custom_command(TARGET Arcanoid POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${BUFFICON} $<TARGET_FILE_DIR:Arcanoid>/textures
    )
endforeach()


set(FONTS
    "${CMAKE_SOURCE_DIR}/src/assets/fonts/First.otf"
)

foreach(FONT ${FONTS})
    add_custom_command(TARGET Arcanoid POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${FONT} $<TARGET_FILE_DIR:Arcanoid>
    )
endforeach()


if(WIN32)
    add_custom_command(
        TARGET Arcanoid
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SFML_BINARY_DIR}/lib/sfml-graphics-d-2.dll
        $<TARGET_FILE_DIR:Arcanoid>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SFML_BINARY_DIR}/lib/sfml-window-d-2.dll
        $<TARGET_FILE_DIR:Arcanoid>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SFML_BINARY_DIR}/lib/sfml-system-d-2.dll
        $<TARGET_FILE_DIR:Arcanoid>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll
        $<TARGET_FILE_DIR:Arcanoid>
        VERBATIM)
endif()

