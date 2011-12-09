#include <ros/ros.h>
#include <joy/Joy.h>
#include "geometry_msgs/Twist.h"
#include <signal.h>
#include <termios.h>
#include <math.h>

#define MIN_DISP 0.7  
#define MIN_ANGLE 0.5
#define NORM_FACTOR 1.0f/6.25f
#define PI 3.1415

using geometry_msgs::Twist;
using namespace std;

class FalconController
{
public:
    FalconController();


private:
    void joyCallback(const joy::Joy::ConstPtr& joy);
    ros::NodeHandle nh_;
    ros::NodeHandle nh2_;

    int linear_, angular_;
    double l_scale_, a_scale_;
    ros::Publisher vel_pub_, force_pub_;
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
    //vel_pub_ = nh_.advertise<Twist>("/RosAria/cmd_vel", 1);
    //vel_pub_ = nh_.advertise<Twist>("Sonar_Falcon", 1);
    vel_pub_ = nh_.advertise<Twist>("test_topic", 1);
    joy_sub_ = nh_.subscribe<joy::Joy>("falconJoy", 10, &FalconController::joyCallback, this);
}

void FalconController::joyCallback(const joy::Joy::ConstPtr& joy)
{
    //Note that x corresponds to horizontal movement of Falcon's grip
    //          y corresponds to vertical movement 
    //          z corresponds to back and forward movement of the grip
    // This is convention is chosen to match human intuition. Therefore 
    // z coord of Falcon maps to forward or backward movement of the robot 
    // (i.e vel.linear.x)
    x = joy->axes[0];
    y = joy->axes[1];
    z = (0.1f- joy->axes[2]);

    //float zoffset = (joy->axes[2] - 0.074);
    float zoffset = (joy->axes[2] + 1.074);

    float angle = atan(x/(zoffset))*180/PI;

    //The robot will move if the use has moved the grip for 
    // a movement larger than the threshold. Otherwise the robot stays still.
    vel.angular.z = abs(angle) > MIN_ANGLE ? -angle : 0.0f;
    vel.linear.x = 100*abs(z) > MIN_DISP ? 100*z*NORM_FACTOR : 0.0f;

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
