#include "JoyStickControllerWithSonar.h"

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
 front_threshold = 0.5;
 side_threshold = 0.3;
	
  nh_.param("axis_linear", linear_, linear_);
  nh_.param("axis_angular", angular_, angular_);
  nh_.param("scale_angular", a_scale_, a_scale_);
  nh_.param("scale_linear", l_scale_, l_scale_);


  vel_pub_ = nh_.advertise<Twist>("/RosAria/cmd_vel", 1000);

  joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10000, &JoysticSonar::joyCallback, this);

  speed_sub_=speed_.subscribe<Odometry>("RosAria/pose",1000, &JoysticSonar::speedCallback,this);

  sonar_sub_ = sonar_.subscribe<hcr_vip::sonar_vip>("sonar_vip",1000, &JoysticSonar::sonarCallback,this); 	
//signal(SIGINT,quit);

}

void JoysticSonar::speedCallback(const Odometry::ConstPtr& speed){
if ((speed->twist.twist.linear.x >= 0.2) || (speed->twist.twist.linear.x <= -0.2)){
	front_threshold = 0.60;
}else{
	front_threshold = 0.40;
}


if ((speed->twist.twist.angular.x >= 0.2) || (speed->twist.twist.angular.z <= -0.2)){
	front_threshold = 0.60;
}else{
	front_threshold = 0.40;
}

}


void JoysticSonar::sonarCallback(const hcr_vip::sonar_vip::ConstPtr& sonar){
ok = false;
sonar_values.distance_front = sonar->distance_front;
sonar_values.angle_front = sonar->angle_front;
sonar_values.distance_back = sonar->distance_back;
sonar_values.angle_back = sonar->angle_back;
sonar_values.turn_right = sonar->turn_right;
sonar_values.turn_left = sonar->turn_left;

	checkDistance(vel.linear.x, vel.angular.z);
	if (!ok){
		STOP();
	}
	else if(ok){	
		vel_pub_.publish(vel);
	}
ok = false;
}

void JoysticSonar::errorMsg(int error){
if(!ok){	
	switch(error){
		case 0 : {
			cout<<"Obstacle at Front " <<sonar_values.distance_front<< "  "<<sonar_values.angle_front<<endl;
			break;
		}
		case 1 : {
			cout<<"Obstacle at Back "<<sonar_values.distance_back<< "  "<<sonar_values.angle_back<<endl;
			break;
		}
		case 2 : {
			cout<<"Obstacle at Right "<<sonar_values.turn_right<<endl;
			break;
		}
		case 3 : {
			cout<<"Obstacle at Left "<<sonar_values.turn_left<<endl;
			break;
		}
		default : {
			cout<<"ALL OK";
			break;
		}
		
	}
}	
}


void JoysticSonar::checkDistance(float linear, float angular){
	if (linear > 0) {
		forward();
		errorMsg(0);
		return ;
	}	
	else if (linear < 0){
		backward();	
		errorMsg(1);
		return ;
	}
	else if (angular < 0){
		turn_Right();
		errorMsg(2);
		return ;
	}
	else if (angular > 0) {
		turn_Left();
		errorMsg(3);
		return ;
	}
	else if( (linear == 0) && (angular == 0) ){
		ok = true;
	}
}

void JoysticSonar::backward(){
	if(
		(sonar_values.distance_back > front_threshold) 
	){
		ok = true;
	}	

}

void JoysticSonar::forward(){
	if  ( 
		(sonar_values.distance_front > front_threshold)
	){
		ok = true;
	}	
}

void JoysticSonar::turn_Right(){
	if ( sonar_values.turn_right > side_threshold){
		ok = true;
	}

}

void JoysticSonar::turn_Left(){
	if (sonar_values.turn_left > side_threshold){
		ok= true;
	}
}

void JoysticSonar::STOP(){
	vel.angular.z = 0.0;
	vel.linear.x = 0.0;
	vel_pub_.publish(vel);
}

void JoysticSonar::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
float linear = 1 * joy->axes[linear_];
float angular = 1 * joy->axes[angular_];

	vel.angular.z = (joy->buttons[7] == 1) ? angular : angular*0.4;
	vel.linear.x = (joy->buttons[7] == 1) ? linear: linear*0.4;

}


int main(int argc, char** argv)
{	
  ros::init(argc, argv, "JoysticSonar");
  JoysticSonar joysticSonar;

  ros::spin();
}
	
