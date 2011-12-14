#include "ros/ros.h"
#include "hcr_vip/sensorMsg.h"
#include <cstdlib>
using namespace std;



class Odom
{
public:
  Odom();

public:
	void test();
  void OCallback(const hcr_vip::sensorMsg::ConstPtr& odom);
  ros::NodeHandle nh_;
  ros::Subscriber odom_sub_;
    hcr_vip::sensorMsg m;
  ros::Publisher vel_pub_;
};

Odom::Odom()
{

	vel_pub_ = nh_.advertise<hcr_vip::sensorMsg>("/SensorMsg", 1);  
	odom_sub_ = nh_.subscribe<hcr_vip::sensorMsg>("SensorMsg2",1, &Odom::OCallback,this);
	test();	
}

void Odom::OCallback(const hcr_vip::sensorMsg::ConstPtr& odom){
	m.range = odom->range;
	m.angle = odom->angle;
	cout<<"hhh: " <<odom->angle<<endl;
	//vel_pub_.publish(m);
	test();
}


void Odom::test(){
		vel_pub_.publish(m);
		cout<<m.angle<<endl;
		ros::Rate loop_rate(5);	
		loop_rate.sleep();
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "sensorMsg");
		Odom odo;
		ros::spin();

}