set(map_generator map_diamond_mipmap_splatmap)
add_subdirectory(shaders)
set(GLFW_ROOT_DIR /usr/local/Cellar/glfw)

add_executable(resource_generator   generator.cpp
                                    command_line_parser.hpp command_line_parser.cpp 
                                    heightmap.cpp heightmap.hpp
                                    splatmap.hpp splatmap.cpp
                                    normalmap.hpp normalmap.cpp)
target_link_libraries(resource_generator PUBLIC heightmap_viewer)

add_executable(presenter_${map_generator} presenter.cpp)
add_dependencies(presenter_${map_generator} shaders_${map_generator})
target_link_libraries(presenter_${map_generator} PUBLIC ecg_framework)



if(WIN32)
    # this allows to find the shaders and other assets via relative paths
    set_property(TARGET presenter_${map_generator} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
endif(WIN32)
