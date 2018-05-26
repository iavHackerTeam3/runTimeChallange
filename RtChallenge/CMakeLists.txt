cmake_minimum_required(VERSION 3.10)
project(RtChallenge)

set(CMAKE_CXX_STANDARD 17)

add_executable(RtChallenge main.cpp utils/tinyxml2.cpp utils/tinyxml2.h model/Target.cpp model/Target.h model/Cross.cpp model/Cross.h model/Edge.cpp model/Edge.h model/TargetData.cpp model/TargetData.h model/Map.cpp model/Map.h)