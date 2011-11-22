#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include "geometry_msgs/Twist.h"
#include <signal.h>
#include <termios.h>
using geometry_msgs::Twist;
using namespace std;

class TeleopThe0
{
public:
  TeleopThe0();

private:
  void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);
  
  ros::NodeHandle nh_;

  int linear_, angular_;
  double l_scale_, a_scale_;
  ros::Publisher vel_pub_;
  ros::Subscriber joy_sub_;
  Twist vel;

  
};
/*
void quit(int sig)
   {
     tcsetattr(kfd, TCSANOW, &cooked);
     ros::shutdown();
     exit(0);
   } 
*/
TeleopThe0::TeleopThe0():
  linear_(1),
  angular_(0)
{

  nh_.param("axis_linear", linear_, linear_);
  nh_.param("axis_angular", angular_, angular_);
  nh_.param("scale_angular", a_scale_, a_scale_);
  nh_.param("scale_linear", l_scale_, l_scale_);


  vel_pub_ = nh_.advertise<Twist>("/RosAria/cmd_vel", 1);


  joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &TeleopThe0::joyCallback, this);
//signal(SIGINT,quit);

}

void TeleopThe0::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{

  //turtlesim::Velocity vel;
  //vel.angular.z = a_scale_*joy->axes[angular_];
  //vel.linear.x = l_scale_*joy->axes[linear_];

//if (joy->buttons[2] == 1){
vel.angular.z = 10 * joy->axes[0];
vel.linear.x = 10 * joy->axes[1];
//}
//else{
//vel.angular.z = joy->axes[0];
//vel.linear.x = joy->axes[1];
//}
	



            ROS_DEBUG("YES");
puts("GET");
  vel_pub_.publish(vel);

}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "teleop_the0");
  TeleopThe0 teleop_turtle;

  ros::spin();
}