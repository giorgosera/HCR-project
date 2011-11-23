#include <ros/ros.h>
#include <joy/Joy.h>
#include "geometry_msgs/Twist.h"
#include <signal.h>
#include <termios.h>
#include <math.h>

#define MIN_DISP 0.099  
#define MIN_ANGLE 2.5
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
    //vel_pub_ = nh_.advertise<Twist>("/RosAria/cmd_vel", 1);
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
    z = joy->axes[2];

    float magnitude = sqrt(x*x + y*y + z*z);
    float angle = acos(z/magnitude)*180/PI;

    magnitude = magnitude > MIN_DISP ? magnitude : 0.0f;
    angle = angle > MIN_ANGLE ? angle : 0.0f;	

    //The robot will move if the use has moved the grip for 
    // a movement larger than the threshold. Otherwise the robot stays still.
    vel.angular.z = angle;
    vel.linear.x = magnitude;

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
