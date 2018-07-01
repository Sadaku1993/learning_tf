cmake_minimum_required(VERSION 2.8.3)
project(learning_tf)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  sensor_msgs
  std_msgs
  tf
)

## System dependencies are found with CMake's conventions
find_package(Boost REQUIRED COMPONENTS system)

find_package(OpenCV 3 REQUIRED)
find_package(PCL REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

find_package(OpenMP)
if (OPENMP_FOUND)
	set (CMAKE_C_FLAG "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

find_package(Eigen3 REQUIRED COMPONENTS system)
include_directories(${Eigen_INCLUDE_DIRS})


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES learning_tf
#  CATKIN_DEPENDS roscpp rospy sensor_msgs std_msgs tf
#  DEPENDS system_lib
)

###########
## Build ##
###########

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(tf_broadcaster_test src/tf_broadcaster_test.cpp)
target_link_libraries(tf_broadcaster_test
  ${catkin_LIBRARIES}
)

add_executable(tf_listener_test src/tf_listener_test.cpp)
target_link_libraries(tf_listener_test
  ${catkin_LIBRARIES}
)

add_executable(frame_tf_broadcaster_test src/frame_tf_broadcaster_test.cpp)
target_link_libraries(frame_tf_broadcaster_test
  ${catkin_LIBRARIES}
)

add_executable(pose_pub_test src/pose_pub_test.cpp)
target_link_libraries(pose_pub_test
  ${catkin_LIBRARIES}
)

add_executable(pose_sub_test src/pose_sub_test.cpp)
target_link_libraries(pose_sub_test
  ${catkin_LIBRARIES}
)

