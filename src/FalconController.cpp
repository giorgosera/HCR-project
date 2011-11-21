#include <ros/ros.h>
#include <joy/Joy.h>
#include "geometry_msgs/Twist.h"
#include <signal.h>
#include <termios.h>
#include <math.h>

using geometry_msgs::Twist;
using namespace std;

class FalconController
{
public:
    FalconController();


private:
    void joyCallback(const joy::Joy::ConstPtr& joy);
    ros::NodeHandle nh_;

    int linear_, angular_;
    double l_scale_, a_scale_;
    ros::Publisher vel_pub_;
    ros::Subscriber joy_sub_;
    Twist vel;
    double x,y,z;  
};

FalconController::FalconController():
  linear_(1),
  angular_(0)
{

    nh_.param("axis_linear", linear_, linear_);
    nh_.param("axis_angular", angular_, angular_);
    nh_.param("scale_angular", a_scale_, a_scale_);
    nh_.param("scale_linear", l_scale_, l_scale_);

    //For normal operation please uncomment the line below and comment the next one.
    vel_pub_ = nh_.advertise<Twist>("/RosAria/cmd_vel", 1);
    //vel_pub_ = nh_.advertise<Twist>("test_topic", 1);
    joy_sub_ = nh_.subscribe<joy::Joy>("falconJoy", 10, &FalconController::joyCallback, this);
}

void FalconController::joyCallback(const joy::Joy::ConstPtr& joy)
{
    x = joy->axes[0];
    y = joy->axes[1];
    z = joy->axes[2];
    
    if (z > 0.102)
    {    
       vel.angular.z = 10*abs(x);
       vel.linear.x = -20*z;
    }
    else if (z < 0.094)  
    {
       vel.angular.z = 10*abs(x);
       vel.linear.x = 20*z;
    }
    else
    {
       vel.angular.z = 0;
       vel.linear.x = 0;
    }

    cout << "Angular z = " << vel.angular.z << endl;
    cout << "Linear x = " << vel.linear.x << endl; 

    vel_pub_.publish(vel);
}


int main(int argc, char** argv)
{	
  ros::init(argc, argv, "FalconController");
  FalconController falconController;

  ros::spin();
}
