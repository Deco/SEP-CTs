cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

find_package(Boost REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

include (FindPkgConfig)
if (PKG_CONFIG_FOUND)
  pkg_check_modules(GAZEBO gazebo)
endif()
include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_library(hello_world SHARED hello_world.cc)
target_link_libraries(hello_world ${GAZEBO_LIBRARIES} ${Boost_LIBRARIES})

add_library(model_push SHARED model_push.cc)
target_link_libraries(model_push ${GAZEBO_LIBRARIES} ${Boost_LIBRARIES})

add_library(camera_push SHARED camera_push.cc)
target_link_libraries(camera_push ${GAZEBO_LIBRARIES} ${Boost_LIBRARIES})

add_library(object_pos SHARED object_pos.cc)
target_link_libraries(object_pos ${GAZEBO_LIBRARIES} ${Boost_LIBRARIES})

add_library(camera_feed SHARED camera_feed.cc)
target_link_libraries(camera_feed ${GAZEBO_LIBRARIES} ${Boost_LIBRARIES})
target_link_libraries(camera_feed ${OpenCV_LIBS} )
