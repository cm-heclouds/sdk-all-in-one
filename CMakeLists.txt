cmake_minimum_required(VERSION 2.8)

project(ont_all )

set(CMAKE_DEBUG_POSTFIX "d")

set(ONT_SOCK_SEND_BUF_SIZE 4096)
set(ONT_SOCK_RECV_BUF_SIZE 2048)
set(ONT_SERVER_ADDRESS "api.heclouds.com")
set(ONT_SERVER_PORT 80)
set(_STATIC 1)

if(WIN32)
  set(_STATIC 1)
elseif(UNIX OR CYGWIN)
  option(_STATIC "static library" ON)
endif(WIN32)

option(_BASE "sdk base" ON)
option(_EDP "edp protocol" OFF)
option(_MQTT "mqtt protocol" OFF)
option(_TEST "test" OFF)
option(_SAMPLE "sample" OFF)

if(WIN32)
    add_definitions(-DONT_OS_WIN)
    add_definitions(-DWIN32_LEAN_AND_MEAN)

    if(MSVC)
        add_definitions(-D_CRT_SECURE_NO_WARNINGS)
        add_definitions(-D_CRT_NONSTDC_NO_DEPRECATE)

        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /wd4819")
        set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /MTd /DONT_DEBUG")
        set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /MT")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4819")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd /DONT_DEBUG")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    endif(MSVC)

    set(ONT_PLATFORM_PERSISTENCE_SUPPORT 1)
    set(ONT_PLATFORM_FLOATING_POINT_SUPPORT 1)
elseif(UNIX OR CYGWIN)
    add_definitions(-DONT_OS_POSIX)

    if(CMAKE_COMPILER_IS_GNUCC)
        #use open source code not support c89
        if(_MP4V2 OR _ONVIF)
            set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -fPIC")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fPIC -fpermissive")
        else()
            set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -fPIC -pedantic -std=c89")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fPIC -pedantic")
        endif(_MP4V2 OR _ONVIF)

        set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -ggdb3")
        set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Os")

        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -ggdb3")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Os")
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-rpath,.")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,.")
    endif(CMAKE_COMPILER_IS_GNUCC)

    set(ONT_PLATFORM_PERSISTENCE_SUPPORT 1)
    set(ONT_PLATFORM_FLOATING_POINT_SUPPORT 1)
    string(TOLOWER "${CMAKE_BUILD_TYPE}" __DEBUG)
    string(COMPARE EQUAL "${__DEBUG}" "debug" ___DEBUG)
    if(___DEBUG)
        add_definitions(-DONT_DEBUG)
    endif(___DEBUG)
endif(WIN32)

set(ONT_SDK_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${ONT_SDK_ROOT}/include)

if(_EDP)
  add_definitions(-DONT_PROTOCOL_EDP)
elseif(_MQTT)
  add_definitions(-DONT_PROTOCOL_MQTT)
endif(_EDP)

configure_file(${ONT_SDK_ROOT}/include/ont/config.h.in ${ONT_SDK_ROOT}/include/ont/config.h)

if(_STATIC)
    set(PLATFORM "${CMAKE_SYSTEM_NAME}_s")
    set(BASE     "base_s")
    set(EDP      "edp_s")
    set(MQTT     "mqtt_s")
else(_STATIC)
    set(PLATFORM "${CMAKE_SYSTEM_NAME}_s")
    set(BASE     "base")
    set(EDP      "edp")
    set(MQTT     "mqtt")
endif(_STATIC)

# platforms
add_subdirectory(platforms)

# protocols
add_subdirectory(protocols)

# tests
if(_TEST)
  add_subdirectory(test)
endif(_TEST)

# samples
if(_SAMPLE)
  add_subdirectory(sample)
endif(_SAMPLE)
