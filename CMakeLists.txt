cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(MyProject main.cpp approx.h
        test/interval_test.cpp
        test/approx_test.h
        test/approx_test.cpp
        newton.h
        test/newton_test.cpp
        test/newton_test.h
)
