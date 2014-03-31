cmake_minimum_required(VERSION 2.8.3)
project(rostld)

find_package(catkin REQUIRED COMPONENTS
  sensor_msgs
  cv_bridge
  roscpp
  std_msgs
  image_transport
)

add_definitions( -DWITH_FFMPEG=ON )
add_definitions( -ggdb -O0 )

# find_package(Boost REQUIRED COMPONENTS system)

#add_message_files(
#  FILES
#  Image.msg
#)

# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

#generate_messages(
#  DEPENDENCIES
#  std_msgs
#)

catkin_package(
  CATKIN_DEPENDS message_runtime
  INCLUDE_DIRS include
#  LIBRARIES rostld
#  CATKIN_DEPENDS roscpp std_msgs
#  DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

# add_library(rostld
#   src/${PROJECT_NAME}/rostld.cpp
# )

###
add_executable(camera_broadcaster src/camera_broadcaster.cpp)
  # add_dependencies(camera_broadcaster rostld_generate_messages_cpp)
  target_link_libraries(camera_broadcaster
    ${catkin_LIBRARIES}
  )
###

###
add_executable(tldtracker src/tldtracker.cpp)
  # add_dependencies(camera_broadcaster rostld_generate_messages_cpp)
  add_library(tldtracker_utils src/tld/tld_utils.cpp)
  add_library(tldtracker_lktracker src/tld/LKTracker.cpp)
  add_library(tldtracker_fernnclassifier src/tld/FerNNClassifier.cpp)
  add_library(tldtracker_tld src/tld/TLD.cpp)
  target_link_libraries(tldtracker_tld
    tldtracker_utils
    tldtracker_lktracker
    tldtracker_fernnclassifier
  )
  target_link_libraries(tldtracker
    tldtracker_utils
    tldtracker_lktracker
    tldtracker_fernnclassifier
    tldtracker_tld
    ${catkin_LIBRARIES}
  )
###

