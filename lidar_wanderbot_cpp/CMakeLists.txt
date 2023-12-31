cmake_minimum_required(VERSION 3.8)
project(lidar_wanderbot_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)

find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

add_executable(wanderbot src/lidar_wanderbot.cpp)
ament_target_dependencies(wanderbot rclcpp sensor_msgs geometry_msgs)

install(TARGETS
  wanderbot
  DESTINATION lib/${PROJECT_NAME})

ament_package()
