cmake_minimum_required(VERSION 2.8.3)
project(aruco_follower)

SET(CMAKE_MODULE_PATH /usr/local/lib/cmake)

find_package(catkin REQUIRED COMPONENTS
	cv_bridge
	image_transport
	roscpp
	sensor_msgs
	std_msgs
)

find_package(OpenCV REQUIRED)

find_package(aruco REQUIRED)

include_directories(
	include
	${catkin_INCLUDE_DIRS}
	${OpenCV_INCLUDE_DIRS}
	${aruco_INCLUDE_DIRS}
)

catkin_package()

add_executable(aruco_follower_node 
	src/aruco_follower_node.cpp 
	src/ArucoFollower.cpp 
)

target_link_libraries(aruco_follower_node
  	${catkin_LIBRARIES}
	${OpenCV_LIBRARIES}
	${aruco_LIBS}
)
