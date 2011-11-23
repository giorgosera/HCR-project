#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include "geometry_msgs/Twist.h"
#include "hcr_vip/sonar_vip.h"
#include <signal.h>
#include <termios.h>
#include "nav_msgs/Odometry.h"
using geometry_msgs::Twist;
using nav_msgs::Odometry;
using namespace std;

class JoysticSonar
{
public:
  JoysticSonar();

private:
	void STOP();
	void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);
	void sonarCallback(const hcr_vip::sonar_vip::ConstPtr& sonar);
	void speedCallback(const Odometry::ConstPtr& speed);
	void checkDistance(float linear, float angular);
	void turn_Left();
	void turn_Right();
	void forward();
	void backward();
	void errorMsg(int msg);
  ros::NodeHandle nh_, sonar_, speed_;

  int linear_, angular_;
  double l_scale_, a_scale_;
  ros::Publisher vel_pub_;
  ros::Subscriber joy_sub_, sonar_sub_, speed_sub_;
  Twist vel;
  hcr_vip::sonar_vip sonar_values;
  bool ok;
  double side_threshold,front_threshold;	
  
};
