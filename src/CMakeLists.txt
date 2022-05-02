aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} sources_in_curdir)


add_library(mysimple2dgameengine "")

target_sources(mysimple2dgameengine PRIVATE ${sources_in_curdir})

find_package(SDL2  REQUIRED)

target_include_directories(mysimple2dgameengine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${SDL2_INCLUDE_DIRS})

target_link_libraries(mysimple2dgameengine ${SDL2_LIBRARIES}  lua)
