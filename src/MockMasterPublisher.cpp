/** 
This is a mock publisher which publishes fake sonar and laser messages.
This is a convenience class to help in situations where our 
trustworthy robots are dead!
**/
#include "ros/ros.h"
#include "hcr_vip/sensorMsg.h"
#include <cstdlib>
using namespace std;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "mock_master_publisher");
  ros::NodeHandle n;
  ros::Publisher mock_pub = n.advertise<hcr_vip::sensorMsg>("mockMasterTopic", 10);
  ros::Rate loop_rate(10);

  int count = 0;
  while (ros::ok())
  {
    hcr_vip::sensorMsg msg;

    msg.range = rand() % 20;
    msg.angle = rand() % 180;
    std::cout << "Publishing mock message:"<<endl;
    std::cout << "------------------------"<<endl;
    std::cout << msg.range << endl;
    std::cout << msg.angle << endl;
    mock_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }
  return 0;
}
