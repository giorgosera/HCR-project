#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include "geometry_msgs/Twist.h"
#include "hcr_vip/sonar_vip.h"
#include <signal.h>
#include <termios.h>
using geometry_msgs::Twist;
using namespace std;

class JoysticSonar
{
public:
  JoysticSonar();

private:
void STOP();
  void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);
  void sonarCallback(const hcr_vip::sonar_vip::ConstPtr& sonar);
   void checkDistance(float linear);
  ros::NodeHandle nh_, sonar_;

  int linear_, angular_;
  double l_scale_, a_scale_;
  ros::Publisher vel_pub_;
  ros::Subscriber joy_sub_, sonar_sub_;
  Twist vel, previous;
  hcr_vip::sonar_vip sonar_values;
  bool ok;
  
};
/*
void quit(int sig)
   {
     tcsetattr(kfd, TCSANOW, &cooked);
     ros::shutdown();
     exit(0);
   } 
*/
JoysticSonar::JoysticSonar():
  linear_(1),
  angular_(0)
{

  nh_.param("axis_linear", linear_, linear_);
  nh_.param("axis_angular", angular_, angular_);
  nh_.param("scale_angular", a_scale_, a_scale_);
  nh_.param("scale_linear", l_scale_, l_scale_);


  vel_pub_ = nh_.advertise<Twist>("/RosAria/cmd_vel", 1);


  joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 1, &JoysticSonar::joyCallback, this);

  sonar_sub_ = sonar_.subscribe<hcr_vip::sonar_vip>("sonar_vip",1, &JoysticSonar::sonarCallback,this); 	
//signal(SIGINT,quit);

}

void JoysticSonar::sonarCallback(const hcr_vip::sonar_vip::ConstPtr& sonar){
ok = false;
sonar_values.distance_front = sonar->distance_front;
sonar_values.angle_front = sonar->angle_front;
sonar_values.distance_back = sonar->distance_back;
sonar_values.angle_back = sonar->angle_back;
cout<<"ala3e"<< vel.linear.x<< "   paliko"<< previous.linear.x<<endl;
	checkDistance(vel.linear.x);
	if (!ok){
		STOP();
	}
	
	else if(ok){
		vel.linear.x = previous.linear.x;
	}	
		
	vel_pub_.publish(vel);
	ok = false;
	}


void JoysticSonar::checkDistance(float linear){

if ((linear > 0) && (sonar_values.distance_front > 0.2)){
ok = true;
}
else if ((linear < 0) && (sonar_values.distance_back > 0.2)){
ok = true;
}
else if (linear == 0){
ok=true;
}
}

void JoysticSonar::STOP(){
	previous.linear.x = vel.linear.x;
	vel.angular.z = 0.0;
	vel.linear.x = 0.0;
	vel_pub_.publish(vel);
}

void JoysticSonar::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
float linear = 10 * joy->axes[linear_];
float angular = 10 * joy->axes[angular_];
//ok = false;

//checkDistance(linear);

previous.linear.x=vel.linear.x;

//if(ok){ 
	vel.angular.z = angular;
	vel.linear.x = linear;
//}
//else{
//	STOP();
//}

//vel.angular.z = angular;

cout<<"joystic change: "<<vel.linear.x<<"   " <<vel.angular.z<<endl;

//vel_pub_.publish(vel);
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "JoysticSonar");
  JoysticSonar joysticSonar;

  ros::spin();
}
