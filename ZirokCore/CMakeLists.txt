cmake_minimum_required(VERSION 3.14)

project(ZirokCore LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if(CMAKE_BUILD_TYPE STREQUAL Release)
      set(PATH_DEBUG_LIB Core/Library/DebugLib/DebugLibNull.cpp)
elseif(CMAKE_BUILD_TYPE STREQUAL Debug AND USE_LOG_FILE STREQUAL 1)
      set(PATH_DEBUG_LIB Core/Library/DebugLib/DebugLibToFile.cpp)
elseif(CMAKE_BUILD_TYPE STREQUAL Debug AND USE_LOG_FILE STREQUAL 2)
      set(PATH_DEBUG_LIB Core/Library/DebugLib/DebugLib.cpp)
endif()

add_library(ZirokCore STATIC
  Core/Generator/Generation.cpp
  Core/Generator/Configuration.cpp
  Core/RoomPatterns/RoomPatterns.cpp
  Core/Generator/RoomSorting.cpp
  Core/Generator/PatternSorting.cpp
  Core/Library/RandomLib/RandomLib.cpp
  ${PATH_DEBUG_LIB}
  Core/BaseDef/InitBaseDef.cpp
  Core/Generator/CoordinatesTools.cpp
  zirokcore.cpp

  Core/Generator/Generator.h
  Core/RoomPatterns/BaseRoomPattern.h
  Core/RoomPatterns/RoomPatterns.h
  Core/Library/RandomLib/RandomLib.h
  Core/Library/DebugLib/DebugLib.h
  Core/BaseDef/BaseDef.h
  zirokcore.h
  ZirokCore_global.h

  Docs/ErrorCode
  Docs/Tasks
  Docs/Rubbish
  Docs/CompletedTasks
)

target_compile_definitions(ZirokCore PUBLIC ZIROKCORE_LIBRARY)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${PROJECT_SOURCE_DIR}/zirokcore.h
                ${PROJECT_SOURCE_DIR}/Build/${CMAKE_BUILD_TYPE}/zirokcore.h

        COMMAND ${CMAKE_COMMAND} -E copy
                ${PROJECT_SOURCE_DIR}/ZirokCore_global.h
                ${PROJECT_SOURCE_DIR}/Build/${CMAKE_BUILD_TYPE}/ZirokCore_global.h)
