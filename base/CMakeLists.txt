#CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
#项目支持c++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 项目信息
set(base_SRCS
  log.cc 
  )

add_library(lion_base ${base_SRCS})
target_link_libraries(lion_base pthread rt)
install(TARGETS lion_base DESTINATION lib)
set(HEADERS
  log.h 
  BlockingQueue.h
  base.h
  )
install(FILES ${HEADERS} DESTINATION include/lion/base)

