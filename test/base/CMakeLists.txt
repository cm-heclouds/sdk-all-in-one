cmake_minimum_required(VERSION 2.8)

set (ONT_SDK_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../..)
include_directories(
    ${ONT_SDK_ROOT}/include
    ${ONT_SDK_ROOT}/protocols/base
)

if(MSVC)
    file(GLOB_RECURSE INC_TEMP FOLLOW_SYMLINKS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
    list(APPEND INC_LIST ${INC_TEMP})
endif(MSVC)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC_LIST)

add_executable(
    test_${BASE}
    ${INC_LIST}
    ${SRC_LIST}
    $<TARGET_OBJECTS:${PLATFORM}_o>
    $<TARGET_OBJECTS:${BASE}_o>
)

LIST(APPEND LIBS
  gtest
  gtest_main
  pthread)

target_link_libraries(test_${BASE} ${LIBS})
