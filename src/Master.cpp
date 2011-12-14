#include "Master.h"

Master::Master():
  front_threshold(0.5),
  side_threshold(0.3),
  inform_threshold(2.0),
  laserBool(false),
  sonarBool(false),
  msgBool(true),
  speed_threshold(0.2)
{
  vel_pub_ = nh_.advertise<Twist>("/RosAria/cmd_vel", 1); 
  sensorMsg_pub_ = speed_.advertise<hcr_vip::sensorMsg>("/SensorMsg", 1);
  joy_sub_ = nh_.subscribe<Twist>("Sonar_Falcon", 1, &Master::joyCallback, this);  
  speed_sub_= speed_.subscribe<Odometry>("RosAria/pose",1, &Master::speedCallback,this);
  sonar_sub_ = sonar_.subscribe<hcr_vip::sonar_vip>("sonar_vip",1, &Master::sonarCallback,this); 
  laser_sub_ = laser_.subscribe<hcr_vip::laser_vip>("laser_vip",1, &Master::laserCallback,this);	
}

void Master::joyCallback(const Twist::ConstPtr& joy){
	vel.angular.z = joy->angular.z;
	vel.linear.x = joy->linear.x; 
}

void Master::speedCallback(const Odometry::ConstPtr& speed){
	if ((speed->twist.twist.linear.x > speed_threshold) || (speed->twist.twist.linear.x < -speed_threshold)){
		front_threshold = 0.60;
	}else{
		front_threshold = 0.30;
	}

	if ((speed->twist.twist.angular.x > speed_threshold) || (speed->twist.twist.angular.z < -speed_threshold)){
		side_threshold = 0.60;
	}else{
		side_threshold = 0.30;
	}
}

void Master::laserCallback(const hcr_vip::laser_vip::ConstPtr& laser){
	laserPtr = laser;
	laserBool = true;
	//checkOK();
}

void Master::sonarCallback(const hcr_vip::sonar_vip::ConstPtr& sonar){
	sonarPtr = sonar;
	sonarBool = true;
	if(laserBool)
		checkOK();
}

void Master::reAdjustSpeed(){
	if(vel.linear.x > speed_threshold){
		vel.linear.x = speed_threshold;
	}
	else if(vel.linear.x < -speed_threshold){
		vel.linear.x = -speed_threshold;
	}

	/*if(vel.angular.z > speed_threshold){
		vel.angular.z = speed_threshold;
	}
	else if(vel.angular.z < -speed_threshold){
		vel.angular.z = -speed_threshold;
	}*/
	vel_pub_.publish(vel);
}

void Master::checkOK(){
	ok = false;
	distanceInform(vel.linear.x, vel.angular.z); 
	checkDistance(vel.linear.x, vel.angular.z);
	if (!ok){
		STOP();
	}
	else if(ok){	
		vel_pub_.publish(vel);
	}
	ok = false;
}

void Master::errorMsg(int error){
	if(!ok){	
		switch(error){
				case 0 : {
					cout<<"Obstacle at Front " <<sensorMsg.range<< "  "<<sensorMsg.angle<<endl;
					publishSensor();
					break;
				}
				case 1 : {
					cout<<"Obstacle at Back "<<sensorMsg.range<< "  "<<sensorMsg.angle<<endl;
					publishSensor();
					break;
				}
				case 2 : {
					cout<<"Obstacle at Right "<<sensorMsg.range<< "  "<<sensorMsg.angle<<endl;
					publishSensor();
					break;
				}
				case 3 : {
					cout<<"Obstacle at Left "<<sensorMsg.range<< "  "<<sensorMsg.angle<<endl;
					publishSensor();
					break;
				}
				default : {
					cout<<"ALL OK";
					break;
				}	
		}	
	}	
}

int Master::addAngle(int x, int angle){
	if ((angle>350) && (x>0)){
		angle = x - (360 - angle);
	}
	else if((angle<10) && (x<0)){
		angle = 360 - (x - angle);
	}
	else{
		angle += x;
	}
	return angle;
}


void Master::publishSensor(){
	static hcr_vip::sensorMsg sonartemp = sensorMsg;
	
	if (sensorMsg.angle >= addAngle(+10,sonartemp.angle) ){
		if (sensorMsg.range >= sonartemp.range + 0.2  ){
			msgBool = true;
		}
		else if (sensorMsg.range <= sonartemp.range - 0.2  ){
			msgBool = true;
		}
	}
	else if (sensorMsg.angle <= addAngle(-10,sonartemp.angle)  ){
		if (sensorMsg.range >= sonartemp.range + 0.2  ){
			msgBool = true;
		}
		else if (sensorMsg.range <= sonartemp.range - 0.2  ){
			msgBool = true;
		}
	}
	else
		msgBool = false;


	if(msgBool)
		sensorMsg_pub_.publish(sensorMsg);
	
	sonartemp = sensorMsg;
}


void Master::distanceInform(float linear, float angular){
	float temp1 = laserPtr->min ;
	int temp2 = laserPtr->angle_min;
	if ((laserPtr->min < inform_threshold) && (linear > 0)){
		sensorMsg.range = laserPtr->min;
		sensorMsg.angle = laserPtr->angle_min;
		reAdjustSpeed();
		publishSensor();
	}

	else if ((sonarPtr->distance_back < inform_threshold) && (linear < 0)){	
		sensorMsg.range = sonarPtr->distance_back;
		sensorMsg.angle = sonarPtr->angle_back;
		reAdjustSpeed();
		publishSensor();
	}
	else if ((sonarPtr->distance_front < inform_threshold) && (linear > 0)){
		sensorMsg.range = sonarPtr->distance_front;
		sensorMsg.angle = sonarPtr->angle_front;
		reAdjustSpeed();
		publishSensor();
	}
	else if ((sonarPtr->turn_right < inform_threshold) && (angular < 0)){
		sensorMsg.range = sonarPtr->turn_right;
		sensorMsg.angle = sonarPtr->turn_right_sensor == "left" ? 270 : 0;
		reAdjustSpeed();
		publishSensor();
	}
	else if ((sonarPtr->turn_left < inform_threshold)&& (angular > 0)){
		sensorMsg.range = sonarPtr->turn_left;
		sensorMsg.angle = sonarPtr->turn_left_sensor == "left" ? 180 : 360;
		reAdjustSpeed();
		publishSensor();
	}
	else{
		if (sonarPtr->distance_back < temp1){
			temp1 = sonarPtr->distance_back;
			temp2 = sensorMsg.angle = sonarPtr->angle_back; 
		}
		else if (sonarPtr->distance_front < temp1){
			temp1 = sonarPtr->distance_front;
			temp2 = sensorMsg.angle = sonarPtr->angle_front; 
		}
		else if (sonarPtr->turn_right < temp1){
			temp1 = sonarPtr->distance_front;
			temp2 = sonarPtr->turn_right_sensor == "left" ? 270 : 0; 
		}
		else if (sonarPtr->turn_right < temp1){
			temp1 = sonarPtr->turn_left;
			temp2 = sonarPtr->turn_left_sensor == "left" ? 180 : 360; 
		}
		publishSensor();
	}
}

void Master::checkDistance(float linear, float angular){
	if (linear > 0){
		forward();
		errorMsg(0);
		//return ;
	}	
	else if (linear < 0){
		backward();	
		errorMsg(1);
		//return ;
	}
	
	if (angular < 0){
		turn_Right();
		errorMsg(2);
		//return ;
	}
	else if (angular > 0) {
		turn_Left();
		errorMsg(3);
		//return ;
	}
	
	if( (linear == 0) && (angular == 0) ){
		ok = true;
	}
}

void Master::backward(){
	if((sonarPtr->distance_back < front_threshold)){
		sensorMsg.range = sonarPtr->distance_back;
		sensorMsg.angle = sonarPtr->angle_back;
		ok = false;
	}
	else{
		ok = true;
	}	
}

void Master::forward(){
	if((sonarPtr->distance_front < front_threshold)){
		sensorMsg.range = sonarPtr->distance_front;
		sensorMsg.angle = sonarPtr->angle_front;
		ok = false;
	}
	else if((laserPtr->straight < front_threshold)){
		sensorMsg.range = laserPtr->straight;
		sensorMsg.angle = laserPtr->angle_straight;
		ok = false;
	}
	else{
		ok = true;
	}	
}

void Master::turn_Right(){
	if (sonarPtr->turn_right < side_threshold){
		ok = false;
		sensorMsg.range = sonarPtr->turn_right;
		sensorMsg.angle = sonarPtr->turn_right_sensor == "left" ? 270 : 0;
	}
	else if((laserPtr->right < side_threshold)){
		sensorMsg.range = laserPtr->right;
		sensorMsg.angle = laserPtr->angle_right;
		ok = false;
	}
	else{
		ok = true;
	}
}

void Master::turn_Left(){
	if(sonarPtr->turn_left < side_threshold){
		sensorMsg.range = sonarPtr->turn_left;
		sensorMsg.angle = sonarPtr->turn_left_sensor == "left" ? 180 : 360;
		ok= false;
	}
	else if((laserPtr->left < side_threshold)){
		sensorMsg.range = laserPtr->left;
		sensorMsg.angle = laserPtr->angle_left;
		ok = false;
	}
	else{
		ok = true;
	}
}

void Master::STOP(){
	vel.angular.z = 0.0;
	vel.linear.x = 0.0;
	vel_pub_.publish(vel);
}

int main(int argc, char** argv){
  ros::init(argc, argv, "Master");
  Master master;
  ros::spin();
}
	
