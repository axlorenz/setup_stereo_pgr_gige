cmake_minimum_required(VERSION 2.8.3)
project(setup_stereo_pgr_gige)
find_package(catkin REQUIRED COMPONENTS roscpp)
catkin_package()


# set include directories for headers and libraries
include_directories( include ${catkin_INCLUDE_DIRS} /usr/include/flycapture)


# set the executable for executing ROS cmds
add_executable(setup_stereo_pgr_gige src/setup_stereo_pgr_gige.cpp src/ini_pgr_gige_stereo)


# add the sourcecode as a "library"
#add_library(stereo_setup src/stereo_setup.cpp)


# target; link against 
link_directories(setup_stereo_pgr_gige /usr/lib)
target_link_libraries(setup_stereo_pgr_gige ${catkin_LIBRARIES} flycapture)

