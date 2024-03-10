cmake_minimum_required(VERSION 3.0)

project(rgn)

find_package(OpenCV REQUIRED)
find_package(realsense2 REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(PCL REQUIRED)
find_package(Python COMPONENTS Interpreter Development REQUIRED)

include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${PCL_INCLUDE_DIRS})
include_directories(${Python_INCLUDE_DIRS})


aux_source_directory(./code/main main)

# aux_source_directory(./code/straightLine straightLine)
# aux_source_directory(./code/realsense/cpp realsense)
# aux_source_directory(./code/net net)
# aux_source_directory(./code code)

# message(CMAKE_RUNTIME_OUTPUT_DIRECTORY)

SET(target_position "../code/yolov5")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${target_position})

add_executable(rgn ${main} ${realsense} ${straightLine} ${featureMatch} ${net})
 
target_link_libraries(rgn ${OpenCV_LIBRARIES})
target_link_libraries(rgn ${realsense2_LIBRARY})
target_link_libraries(rgn ${PCL_LIBRARIES})
target_link_libraries(rgn ${Python_LIBRARIES})