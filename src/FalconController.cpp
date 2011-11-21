#include <ros/ros.h>
#include <joy/Joy.h>
#include "geometry_msgs/Twist.h"
#include <signal.h>
#include <termios.h>
using geometry_msgs::Twist;
using namespace std;
  int x;

class TeleopThe0
{
public:
  TeleopThe0();


private:
  void joyCallback(const joy::Joy::ConstPtr& joy);
  
  ros::NodeHandle nh_;

  int linear_, angular_;
  double l_scale_, a_scale_;
  ros::Publisher vel_pub_;
  ros::Subscriber joy_sub_;
  Twist vel;
  double start1, start2;
  
  
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


  joy_sub_ = nh_.subscribe<joy::Joy>("falconJoy", 10, &TeleopThe0::joyCallback, this);
//signal(SIGINT,quit);

}

void TeleopThe0::joyCallback(const joy::Joy::ConstPtr& joy)
{

  //turtlesim::Velocity vel;
  //vel.angular.z = a_scale_*joy->axes[angular_];
  //vel.linear.x = l_scale_*joy->axes[linear_];

//if (joy->buttons[2] == 1){
if (x<100){
start1 += joy->axes[0];
start2 += joy->axes[1];
x++;
cout<<"empika"<< start1<<endl;

}

if (x==100){
double t =  100.0;
start1/=t;
start2/=t;
x++;
}


if (x>=100){
 vel.angular.z = 100 * (joy->axes[0] - start1);
 vel.linear.x = 100 * (joy->axes[1] - start2);
 cout<<start1<< "  " << joy->axes[0]<<"  "<<x<<endl;
x++;

}
double test = 0.5;

if((vel.angular.z < test) && (vel.linear.x < test) && (x>100)){
	x=0;

	cout<<"eise vlakas"<<endl;
}



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
  x=0;	
  ros::init(argc, argv, "teleop_the0");
  TeleopThe0 teleop_turtle;

  ros::spin();
}
