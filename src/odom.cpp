#include <ros/ros.h>
#include <signal.h>
#include <termios.h>
#include "math.h"
#include "string.h"
#include "nav_msgs/Odometry.h"
using namespace std;
using nav_msgs::Odometry;

class Odom
{
public:
  Odom();

private:
  void OCallback(const Odometry::ConstPtr& odom);
  ros::NodeHandle nh_;
  ros::Publisher vel_pub_;
  ros::Subscriber odom_sub_;
};

Odom::Odom()
{
	vel_pub_ = nh_.advertise<Odometry>("/odom", 1);  
	odom_sub_ = nh_.subscribe<Odometry>("RosAria/pose",1, &Odom::OCallback,this);
}

void Odom::OCallback(const Odometry::ConstPtr& odom){
	vel_pub_.publish(odom);
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "Odom");
	Odom odo;
	ros::spin();
}
