cmake_minimum_required(VERSION 3.20..3.31)

project(InterClassCallbacks LANGUAGES CXX)


set(CXX_STANDARD 17)


# Target Main, links with stk and adds some compile time flags.
add_executable(Main src/main.cpp src/TermInput.cpp src/SineGen.cpp)
include_directories(Main include)

add_library(Utility src/Utility.cpp)
target_link_libraries(Main Utility)

add_library(SynthConfig src/SynthConfig.cpp)
target_link_libraries(Main SynthConfig)

target_compile_definitions(Main PRIVATE -D__OS_LINUX__)
target_include_directories(Main PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(Main stk) 
target_link_libraries(Main rtaudio)



# Target StkNoise

add_executable(StkNoise src/StkNoise.cpp)
target_link_libraries(StkNoise stk)


# Target StkSine
add_executable(StkSine src/StkSine.cpp)
target_link_libraries(StkSine stk)


# Target StkRT
add_executable(StkRT src/StkRT.cpp)
target_compile_definitions(StkRT PRIVATE -D__LINUX_ALSA__)
target_link_libraries(StkRT stk)


#Target T
add_executable(T src/T.cpp)
target_compile_definitions(T PRIVATE -D__LINUX_ALSA__)
target_link_libraries(T stk)
target_link_libraries(T rtaudio)