#CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
#项目支持c++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 项目信息
project (lion)
ADD_SUBDIRECTORY(base)
ADD_SUBDIRECTORY(test)
