target_include_directories(KDEAirPods PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB_RECURSE BACKEND_SOURCES src/*.cpp)
target_sources(KDEAirPods PRIVATE ${BACKEND_SOURCES})
target_link_libraries(KDEAirPods PRIVATE sdbus-c++ bluetooth)