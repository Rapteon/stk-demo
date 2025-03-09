cmake_minimum_required(VERSION 3.20..3.31)

project(InterClassCallbacks LANGUAGES CXX)


set(CXX_STANDARD 17)


# Target Main, links with stk and adds some compile time flags.
add_executable(Main src/main.cpp src/TermInput.cpp src/SineGen.cpp)

target_compile_definitions(Main PRIVATE -D__OS_LINUX__)
target_include_directories(Main PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(Main stk) 



# Target StkNoise

add_executable(StkNoise src/StkNoise.cpp)
target_link_libraries(StkNoise stk)


# Target StkSine
add_executable(StkSine src/StkSine.cpp)
target_link_libraries(StkSine stk)

