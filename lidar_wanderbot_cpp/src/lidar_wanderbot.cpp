#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include<iostream>
#include<vector>

#include "rclcpp/rclcpp.hpp"
#include <sensor_msgs/msg/laser_scan.hpp>
#include <geometry_msgs/msg/twist.hpp>

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */

class LidarWanderBot : public rclcpp::Node
{
  public:
    LidarWanderBot()
    : Node("lidar_wanderbot")
    {
      publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
      subscription_ = this->create_subscription<sensor_msgs::msg::LaserScan>(
      "scan", 10, std::bind(&LidarWanderBot::lidar_callback, this, std::placeholders::_1));
    }

  private:
    void lidar_callback(const sensor_msgs::msg::LaserScan::SharedPtr msg)
    {
      std::vector<float> forward(msg->ranges.begin()+315, msg->ranges.end());
      for(int i=0; i<45; i++){
        forward.push_back(msg->ranges[i]);
      }
      std::vector<float> right(msg->ranges.begin()+45, msg->ranges.begin()+135);
      std::vector<float> back(msg->ranges.begin()+135,msg->ranges.begin()+225);
      std::vector<float> left(msg->ranges.begin()+225, msg->ranges.begin()+315);
      if(*min_element(forward.begin(), forward.end()) > 0.4){
        move_forward();
      }else if(*min_element(right.begin(), right.end()) > 0.4){
        move_right();
      }else if(*min_element(left.begin(), left.end()) >  0.4){
        move_left();
      }else if(*min_element(back.begin(), back.end()) > 0.4){
        move_back();
      }else{
        stop();
      }
      

    }

    void move_forward()
    {
        auto msg1 = std::make_shared<geometry_msgs::msg::Twist>();
        msg1->linear.x = 0.5;
        msg1->angular.z = 0.0;
        publisher_->publish(*msg1);
    }

    void move_left()
    {
        auto msg1 = std::make_shared<geometry_msgs::msg::Twist>();
        msg1->linear.x = 0.0;
        msg1->angular.z = -0.5;
        publisher_->publish(*msg1);
    }

    void move_right()
    {
        auto msg1 = std::make_shared<geometry_msgs::msg::Twist>();
        msg1->linear.x = 0.0;
        msg1->angular.z = 0.5;
        publisher_->publish(*msg1);
    }

    void move_back()
    {
        auto msg1 = std::make_shared<geometry_msgs::msg::Twist>();
        msg1->linear.x = -1.0;
        msg1->angular.z = 0.0;
        publisher_->publish(*msg1);
    }


    void stop()
    {
        auto msg1 = std::make_shared<geometry_msgs::msg::Twist>();
        msg1->linear.x = 0.0;
        msg1->angular.z = 0.0;
        publisher_->publish(*msg1);
    }

    // rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr subscription_;
    size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<LidarWanderBot>());
  rclcpp::shutdown();
  return 0;
}