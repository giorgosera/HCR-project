#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include "geometry_msgs/Twist.h"
#include "hcr_vip/sonar_vip.h"
#include "hcr_vip/laser_vip.h"
#include <signal.h>
#include <termios.h>
#include "sensor_msgs/PointCloud.h"
#include "sensor_msgs/LaserScan.h"
#include "math.h"
#include "string.h"

#define PI 3.14159265
using geometry_msgs::Twist;

using namespace std;


class Laser
{
public:
  Laser();

private:
  void sonarCallback(const sensor_msgs::PointCloud::ConstPtr& sonar);
  void laserCallback(const sensor_msgs::LaserScan::ConstPtr& pointCloud);
  ros::NodeHandle nh_;

  int linear_, angular_;
  double l_scale_, a_scale_;
  ros::Publisher vel_pub_;
  ros::Subscriber joy_sub_;
  Twist vel;
  int sensors; 	

  hcr_vip::sonar_vip sonar_values; 
  hcr_vip::laser_vip laser_values;

  
};
Laser::Laser():
  linear_(1),
  angular_(0)
  
{

  nh_.param("axis_linear", linear_, linear_);
  nh_.param("axis_angular", angular_, angular_);
  nh_.param("scale_angular", a_scale_, a_scale_);
  nh_.param("scale_linear", l_scale_, l_scale_);


  vel_pub_ = nh_.advertise<hcr_vip::laser_vip>("/laser_vip", 10);
 
    joy_sub_ = nh_.subscribe<sensor_msgs::LaserScan>("/scan",10,&Laser::laserCallback,this);
//signal(SIGINT,quit);
}

void Laser::laserCallback(const sensor_msgs::LaserScan::ConstPtr& pointCloud){
/*
cout<<"0: ";
cout<<pointCloud->ranges[0]<<endl;
cout<<"90: ";
cout<<pointCloud->ranges[90]<<endl;
cout<<"180: ";
cout<<pointCloud->ranges[180]<<endl;
*/

double range=100;
double index;

for(int i=30; i<pointCloud->ranges.size(); i++){
   if (pointCloud->ranges[i] < range){
	range = pointCloud->ranges[i];
	index = i > 90 ? 360 - (i - 90) : 90 - i;
	}
}
cout<<"Danger min: "<<index<<" Degrees     Distance: "<<range<<endl;

double range1=100;
double index1;

for(int i=30; i<151; i++){
   if (pointCloud->ranges[i] < range1){
	range1 = pointCloud->ranges[i];
	index1 = i > 90 ? 360 - (i - 90) : 90 - i;
	}
}
cout<<"Danger Straight: "<<index1<<" Degrees     Distance: "<<range1<<endl;



double range2=100;
double index2;

for(int i=0; i<100; i++){
   if (pointCloud->ranges[i] < range2){
	range2 = pointCloud->ranges[i];
	index2 = i > 90 ? 360 - (i - 90) : 90 - i;
	}
}
cout<<"Danger Right: "<<index2<<" Degrees     Distance: "<<range2<<endl;



double range3=100;
double index3;

for(int i=80; i<pointCloud->ranges.size(); i++){
   if (pointCloud->ranges[i] < range3){
	range3 = pointCloud->ranges[i];
	index3 = i > 90 ? 360 - (i - 90) : 90 - i;
	}
}
cout<<"Danger Left: "<<index3<<"Degrees     Distance: "<<range3<<endl;
cout<<"*****************************"<<endl;

laser_values.straight = range1;
laser_values.angle_straight = index1;

laser_values.right = range2;
laser_values.angle_right = index2;

laser_values.left = range3;
laser_values.angle_left = index3;

laser_values.min = range;
laser_values.angle_min = index;

 ros::Rate loop_rate(5);
vel_pub_.publish(laser_values);
loop_rate.sleep();
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "laser");
 //ros::Rate loop_rate(1);
  Laser laser;

  ros::spin();
}
