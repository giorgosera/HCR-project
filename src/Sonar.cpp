#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include "geometry_msgs/Twist.h"
#include "hcr_vip/sonar_vip.h"
#include <signal.h>
#include <termios.h>
#include "sensor_msgs/PointCloud.h"
#include "math.h"
#include "string.h"
#define PI 3.14159265
using geometry_msgs::Twist;
using namespace std;

class Sonar
{
public:
  Sonar();

private:
  void sonarCallback(const sensor_msgs::PointCloud::ConstPtr& sonar);

  ros::NodeHandle nh_;
  ros::Publisher vel_pub_;
  ros::Subscriber joy_sub_;
  int sensors; 	
  hcr_vip::sonar_vip sonar_values;  
};

Sonar::Sonar()
{
  vel_pub_ = nh_.advertise<hcr_vip::sonar_vip>("/sonar_vip", 1);
  joy_sub_ = nh_.subscribe<sensor_msgs::PointCloud>("/RosAria/sonar", 1, &Sonar::sonarCallback, this);
}

void Sonar::sonarCallback(const sensor_msgs::PointCloud::ConstPtr& pointCloud){
sensors = pointCloud->points.size(); //set the number of sensors on the robot

double r[16];
double arg[16];
double min_front = 100;
double min_back = 100;
double min_left =100;
double min_right = 100;
int index_front;
int index_back;
string turn_left_sensor;
string turn_right_sensor;

for(int i=1; i<7; i++){
r[i] = pow(pointCloud->points[i].x,2) + pow(pointCloud->points[i].y,2);
arg[i] = atan(pointCloud->points[i].x / pointCloud->points[i].y)* 180 / PI;
	if (r[i] < min_front){
		min_front = r[i];
		index_front=i;
	}
}
int angle_front;
if (index_front < 5){
angle_front = 270 + index_front * 22.5;
}
else if(index_front > 4){
angle_front = 22.5 + (index_front-4) * 22.5;
}

for(int i=9; i<sensors-1; i++){
r[i] = pow(pointCloud->points[i].x,2) + pow(pointCloud->points[i].y,2);
arg[i] = atan(pointCloud->points[i].x / pointCloud->points[i].y)* 180 / PI;
	if (r[i] < min_back){
		min_back = r[i];
		index_back=i;
	}
}

int angle_back;
if (index_back > 11){
angle_back = 180 + (-index_back + 15) * 22.5;
}
else if(index_back < 12){
angle_back = 22.5 + (index_back - 5) * 22.5 ;
}

double temp[2];
temp[0]=  pow(pointCloud->points[0].x,2) + pow(pointCloud->points[0].y,2);
temp[1]=  pow(pointCloud->points[8].x,2) + pow(pointCloud->points[8].y,2);
 
if (temp[0] > temp[1]){
min_left = temp[1];
turn_left_sensor = "right";
}
else{
min_left = temp[0];
turn_left_sensor = "left";
}

temp[0]=  pow(pointCloud->points[7].x,2) + pow(pointCloud->points[7].y,2);
temp[1]=  pow(pointCloud->points[15].x,2) + pow(pointCloud->points[15].y,2);
 
if (temp[0] > temp[1]){
min_right = temp[1];
turn_right_sensor = "left";
}
else{
min_right = temp[0];
turn_right_sensor = "right";
}

sonar_values.distance_front = min_front;
sonar_values.angle_front = angle_front;
sonar_values.distance_back = min_back;
sonar_values.angle_back = angle_back;
sonar_values.turn_left = min_left;
sonar_values.turn_right = min_right;
sonar_values.turn_left_sensor = turn_left_sensor;
sonar_values.turn_right_sensor = turn_right_sensor ;
cout<<"Sensors: "<<sensors<<endl;
cout<<"Front obstacle at: "<<min_front<< "  "<<angle_front<<endl;
cout<<"Back obstacle at: "<<min_back<< "  "<<angle_back<<endl;
cout<< "Left obstacle at: "<<min_left<<"  sensor: "<<turn_left_sensor<<endl;   
cout<< "Right obstacle at: "<<min_right<< "  sesnor: "<<turn_right_sensor<<endl;
//ROS_DEBUG("YES");
//puts("GET");

//ros::Rate loop_rate(5);
vel_pub_.publish(sonar_values);
//loop_rate.sleep();
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "sonar");
  Sonar sonar;	
  ros::spin();
}
