#include "Master.h"

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
	
  //nh_.param("axis_linear", linear_, linear_);
  //nh_.param("axis_angular", angular_, angular_);
  //nh_.param("scale_angular", a_scale_, a_scale_);
  //nh_.param("scale_linear", l_scale_, l_scale_);



  vel_pub_ = nh_.advertise<Twist>("/RosAria/cmd_vel", 1);

  
  //joy_sub_ = nh_.subscribe<Twist>("Sonar_Falcon", 1, &JoysticSonar::joyCallback, this);

  joy_sub_ = nh_.subscribe<Twist>("joy", 1, &JoysticSonar::joyCallback, this);
   
  sensorMsg_pub_ = speed_.advertise<hcr_vip::sensorMsg>("/SensorMsg", 1);

  speed_sub_= speed_.subscribe<Odometry>("RosAria/pose",1, &JoysticSonar::speedCallback,this);

  sonar_sub_ = sonar_.subscribe<hcr_vip::sonar_vip>("sonar_vip",1, &JoysticSonar::sonarCallback,this); 

  laser_sub_ = laser_.subscribe<hcr_vip::laser_vip>("laser_vip",1, &JoysticSonar::laserCallback,this);	
//signal(SIGINT,quit);

}

void JoysticSonar::laserCallback(const hcr_vip::laser_vip::ConstPtr& laser){
/*
cout<<"hello"<<endl;
cout<<laser->min<<endl;
cout<<laser->angle_min<<endl;
cout<<laser->straight<<endl;
cout<<laser->angle_straight<<endl;
cout<<laser->right<<endl;
cout<<laser->angle_right<<endl;
cout<<laser->left<<endl;
cout<<laser->angle_left<<endl;
*/


laserPtr = laser;
cout<<laserPtr->min<<endl;
checkOK();

}


void JoysticSonar::speedCallback(const Odometry::ConstPtr& speed){
if ((speed->twist.twist.linear.x >= 0.2) || (speed->twist.twist.linear.x <= -0.2)){
	front_threshold = 0.60;
}else{
	front_threshold = 0.40;
}


if ((speed->twist.twist.angular.x >= 0.2) || (speed->twist.twist.angular.z <= -0.2)){
	side_threshold = 0.60;
}else{
	side_threshold = 0.40;
}

}


void JoysticSonar::sonarCallback(const hcr_vip::sonar_vip::ConstPtr& sonar){
ok = false;
sonarPtr = sonar;
sonar_values.distance_front = sonar->distance_front;
sonar_values.angle_front = sonar->angle_front;
sonar_values.distance_back = sonar->distance_back;
sonar_values.angle_back = sonar->angle_back;
sonar_values.turn_right = sonar->turn_right;
sonar_values.turn_left = sonar->turn_left;

checkOK();
}


void JoysticSonar::checkOK(){
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

sensorMsg_pub_.publish(sensorMsg);
			break;
		}
		case 1 : {
			cout<<"Obstacle at Back "<<sonar_values.distance_back<< "  "<<sonar_values.angle_back<<endl;

sensorMsg_pub_.publish(sensorMsg);
			break;
		}
		case 2 : {
			cout<<"Obstacle at Right "<<sonar_values.turn_right<<endl;

sensorMsg_pub_.publish(sensorMsg);
			break;
		}
		case 3 : {
			cout<<"Obstacle at Left "<<sonar_values.turn_left<<endl;


sensorMsg_pub_.publish(sensorMsg);
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
	
	if (angular < 0){
		turn_Right();
		errorMsg(2);
		return ;
	}
	else if (angular > 0) {
		turn_Left();
		errorMsg(3);
		return ;
	}
	
	if( (linear == 0) && (angular == 0) ){
		ok = true;
	}
}

void JoysticSonar::backward(){
	if(
		(sonarPtr->distance_back > front_threshold) 
	){
		ok = true;
	}
	else{
		sensorMsg.range = sonarPtr->distance_back;
		sensorMsg.angle = sonarPtr->angle_back;
	}	

}

void JoysticSonar::forward(){
	if  ( 
		(sonarPtr->distance_front < front_threshold)
	){
		sensorMsg.range = sonarPtr->distance_front;
		sensorMsg.angle = sonarPtr->angle_front;
		ok = false;
	}
	else if  ( 
		(laserPtr->straight < front_threshold)
	){
		sensorMsg.range = laserPtr->straight;
		sensorMsg.angle = laserPtr->angle_straight;
		ok = false;
	}
	else{
		ok = true;
	}	
}

void JoysticSonar::turn_Right(){
	if ( sonarPtr->turn_right < side_threshold){
		ok = false;
		sensorMsg.range = sonarPtr->turn_right;
		sensorMsg.angle = sonarPtr->turn_right_sensor == "left" ? 270 : 0;
	}
	else if  ( 
		(laserPtr->right < side_threshold)
	){
		sensorMsg.range = laserPtr->right;
		sensorMsg.angle = laserPtr->angle_right;
		ok = false;
	}
	else{
		ok = true;
	}

}

void JoysticSonar::turn_Left(){
	if (sonarPtr->turn_left < side_threshold){
		sensorMsg.range = sonarPtr->turn_left;
		sensorMsg.angle = sonarPtr->turn_left_sensor == "left" ? 180 : 360;
		ok= false;
	}
	else if  ( 
		(laserPtr->left < side_threshold)
	){
		sensorMsg.range = laserPtr->left;
		sensorMsg.angle = laserPtr->angle_left;
		ok = false;
	}
	else{
		ok = true;
	}
}


void JoysticSonar::STOP(){
	vel.angular.z = 0.0;
	vel.linear.x = 0.0;
	vel_pub_.publish(vel);
}

void JoysticSonar::joyCallback(const Twist::ConstPtr& joy)
{
	vel.angular.z = joy->angular.z;
	vel.linear.x = joy->linear.x;
}


int main(int argc, char** argv)
{	
  ros::init(argc, argv, "Master");

  JoysticSonar master;

  ros::spin();
}
	
