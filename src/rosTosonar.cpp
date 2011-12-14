#include <ros/ros.h>
#include <signal.h>
#include <termios.h>
#include "math.h"
#include "string.h"
#include "sensor_msgs/PointCloud.h"
using namespace std;

class Odom
{
public:
  Odom();

private:
  void OCallback(const sensor_msgs::PointCloud::ConstPtr& odom);
  ros::NodeHandle nh_;
  ros::Publisher vel_pub_;
  ros::Subscriber odom_sub_;
};

Odom::Odom()
{
	vel_pub_ = nh_.advertise<sensor_msgs::PointCloud>("/sonar", 1);  
	odom_sub_ = nh_.subscribe<sensor_msgs::PointCloud>("RosAria/sonar",1, &Odom::OCallback,this);
}

void Odom::OCallback(const sensor_msgs::PointCloud::ConstPtr& odom){
	vel_pub_.publish(odom);
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "toSonar");
	Odom odo;
	ros::spin();
}
