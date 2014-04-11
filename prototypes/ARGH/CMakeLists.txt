
cmake_minimum_required(VERSION 2.6) 
project(thermalprototype)

include_directories(
  libserial/source/
  libmicrohttpd
  libmicrohttpd/src/include
  libmicrohttpd/src/microhttpd
  websocketpp/
)

#add_definitions(-DHTTPS_SUPPORT)
add_definitions("-ggdb -O0 -Wgnu-static-float-init")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -ggdb")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -ggdb")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O0 -ggdb")

FILE(GLOB ProjectSources src/*.cpp)
set(LibMicroHTTPDSources
  libmicrohttpd/src/microhttpd/base64.c
  libmicrohttpd/src/microhttpd/basicauth.c
  libmicrohttpd/src/microhttpd/connection.c
  #libmicrohttpd/src/microhttpd/connection_https.c
  libmicrohttpd/src/microhttpd/daemon.c
  libmicrohttpd/src/microhttpd/digestauth.c
  libmicrohttpd/src/microhttpd/internal.c
  libmicrohttpd/src/microhttpd/md5.c
  libmicrohttpd/src/microhttpd/memorypool.c
  libmicrohttpd/src/microhttpd/postprocessor.c
  libmicrohttpd/src/microhttpd/reason_phrase.c
  libmicrohttpd/src/microhttpd/response.c
  libmicrohttpd/src/microhttpd/tsearch.c
)

add_executable(thermalprototype
  ${LibMicroHTTPDSources}
  ${ProjectSources}
  libserial/source/debug_serial.cpp
  libserial/source/serial_connection.cpp
  libserial/source/serial_receive.cpp
  libserial/source/serial_server.cpp
  libserial/source/serial_send.cpp
)

if(UNIX)
  target_link_libraries(thermalprototype pthread ${Boost_LIBRARIES})

  find_package( Boost 1.40 COMPONENTS system program_options REQUIRED )
  include_directories( ${Boost_INCLUDE_DIR} )
  target_link_libraries(thermalprototype
    ${Boost_SYSTEM_LIBRARY}
  )
endif(UNIX)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "cmake_modules/")
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(thermalprototype ${SFML_LIBRARIES})
endif()

install(TARGETS thermalprototype DESTINATION bin)


