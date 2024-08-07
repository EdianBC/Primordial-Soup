cmake_minimum_required(VERSION 3.10)
project(MySFMLProject)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

add_executable(PrimordialSoup.exe src/main.cpp)
target_link_libraries(PrimordialSoup.exe sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
