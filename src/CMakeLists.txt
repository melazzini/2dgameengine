aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} sources_in_curdir)

include(FetchContent)

# In this example we are picking a specific tag.
# You can also pick a specific commit, if you need to.
FetchContent_Declare(GSL
    GIT_REPOSITORY "https://github.com/microsoft/GSL"
    GIT_TAG "v3.1.0"
)

FetchContent_MakeAvailable(GSL)

add_library(mysimple2dgameengine "")

target_sources(mysimple2dgameengine PRIVATE ${sources_in_curdir})

set_target_properties(mysimple2dgameengine 
                        PROPERTIES 
                        CXX_STANDARD 20 
                        CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/modules/")

find_package(SDL2  REQUIRED)
find_package(SDL2_image REQUIRED)

target_include_directories(mysimple2dgameengine 
                                                PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} 
                                                "${CMAKE_CURRENT_SOURCE_DIR}/../lib/glm"  
                                                ${SDL2_INCLUDE_DIRS} 
                                                {SDL2_IMAGE_INCLUDE_DIRS})

target_link_libraries(mysimple2dgameengine ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARY}  lua GSL)

# add_compile_options(-lSDL_Image)