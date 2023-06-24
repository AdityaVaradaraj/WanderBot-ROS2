# WanderBot-ROS2
LiDAR-based basic collision avoidancce turtlebot using ROS2, Gazebo and C++

## Requirements:
ROS2
C++
Turtlebot3 packages
Gazebo
Ubuntu 22.04

## Instructions:
1) Download the package and move it to your ROS2 Workspace.
2) Run the following commands in one terminal:
   ```console
   rosdep install -i --from-path src --rosdistro humble -y
   ```
   ```console
   colcon build --packages-select lidar_wanderbot_cpp
   ```
   ```console
   source install setup.bash
   ```
3) On another terminal, run:
   ```console
   ros2 launch turtlebot3_gazebo turtlebot3_world.launch.py
   ```
   ```console
   ros2 run lidar_wanderbot_cpp wanderbot
   ```

https://github.com/AdityaVaradaraj/WanderBot-ROS2/assets/34472717/a93642b2-58d2-4e27-acc9-6c41fabc30ec

