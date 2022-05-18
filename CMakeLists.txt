cmake_minimum_required(VERSION 3.1)

project(GameOfLife)

set(SFML_BUILD_DOCS FALSE)

set(SOURCES
    src/main.cpp
    
    src/app.cpp
    src/movable_view.cpp
    src/conway_automaton.cpp
    src/gui/gui.cpp
    src/gui/gui_button.cpp

    src/app.h
    src/movable_view.h
    src/conway_automaton.h
    src/gui/gui.h
    src/gui/gui_button.h

    src/gui/file_dialog/tinyfiledialogs.h
    src/gui/file_dialog/tinyfiledialogs.cpp
    src/util/hsv_to_rgb.h
)



# Copy images from source to build folder

file(GLOB RESOURCES_IMAGES "resources/images/*.png") 
file(COPY ${RESOURCES_IMAGES} DESTINATION ${CMAKE_BINARY_DIR}/bin/resources/images/) 

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
add_executable(GameOfLife WIN32 ${SOURCES})
set_target_properties(GameOfLife PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
target_link_libraries(GameOfLife sfml-graphics)

