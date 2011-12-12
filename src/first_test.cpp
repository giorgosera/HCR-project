//=================================================================================================
// Copyright (c) 2011, Paul Filitchkin, Brian Satzinger
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the UCSB Robotics Lab nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//=================================================================================================

// Local includes
#include "create_kinect/Mode.h"
#include "create_kinect/PointStatus.h"
#include "remote_modes.h"

// ROS core
#include <ros/ros.h>
#include <boost/thread/mutex.hpp>

// PCL includes
#include <pcl_ros/point_cloud.h>
#include <pcl/point_types.h>

// iRobot Create control
#include <geometry_msgs/Twist.h>
#include <joy/Joy.h>

// Rviz related
#include <visualization_msgs/Marker.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <iterator>

using namespace std;

//Typedefs
typedef pcl::PointXYZRGB PointT;
typedef pcl::PointCloud<PointT> CloudT;

sensor_msgs::PointCloud2ConstPtr cloud_, cloud_old_;
boost::mutex m;
unsigned char mode = create_kinect::stop;
unsigned char modePrev = create_kinect::stop;
unsigned actionTimerCount = 0;

ros::Publisher velPub; // Create publisher

float linear, linearPrev;
float angular, angularPrev;
double linScale, angScale;

struct SRanges
{
  double yMin;
  double yMax;
  double zMin;
  double zMax;
  double xRMin;
  double xLMin;
  double xRMax;
  double xLMax;
};

// It seemed too convoluted to use std_msgs::RGBA_ so I added my own struct
struct SRgba
{
  double r;
  double g;
  double b;
  double a;
};

//==================================================================================================
// Description:
//   This callback intercepts the message from the ROS Kinect node
//==================================================================================================
void CloudCallback (const sensor_msgs::PointCloud2ConstPtr& cloud)
{
  m.lock();
  cloud_ = cloud;
  m.unlock();
}

//==================================================================================================
//==================================================================================================
void ModeCallback (const create_kinect::Mode m)
{

  modePrev = mode;
  mode = m.mode;

  if(mode == create_kinect::autonomous)
  {
      ROS_INFO("Mode: Autonomous");
  }
  else if(mode == create_kinect::stop)
  {
      ROS_INFO("Mode: Stop");
  }
  else if(mode == create_kinect::manual)
  {
      ROS_INFO("Mode: Manual");
  }
  else if(mode == create_kinect::turnAround)
  {
      actionTimerCount = 0;
      ROS_INFO("Mode: Turn Around");
  }
}


//==================================================================================================
//==================================================================================================
void DefaultRanges(struct SRanges& r)
{
  r.xLMin = -1.0f;
  r.xLMax = -0.2f;
  r.xRMin =  0.2f;
  r.xRMax =  1.0f;
  r.yMin  = -0.25f;
  r.yMax  =  0.9f;
  r.zMin  = -1.0f;
  r.zMax  =  4.0f;
}

//==================================================================================================
//==================================================================================================
void ReadRangeParameters(ros::NodeHandle& nh, struct SRanges& r)
{

  double val;

  if (nh.getParam("/first_test/xl_min", val)) r.xLMin = val;
  if (nh.getParam("/first_test/xl_max", val)) r.xLMax = val;
  if (nh.getParam("/first_test/xr_min", val)) r.xRMin = val;
  if (nh.getParam("/first_test/xr_max", val)) r.xRMax = val;
  if (nh.getParam("/first_test/y_min", val))  r.yMin = val;
  if (nh.getParam("/first_test/y_max", val))  r.yMax = val;
  if (nh.getParam("/first_test/z_min", val))  r.zMin = val;
  if (nh.getParam("/first_test/z_max", val))  r.zMax = val;

}

//==================================================================================================
//==================================================================================================
void PublishBoundMarker(
    ros::Publisher& pub,
    unsigned id,
    const tf::Vector3& pos,
    const tf::Vector3& scale,
    struct SRgba& col)
{

  visualization_msgs::Marker m;

  m.header.frame_id = "/openni_rgb_optical_frame";
  m.header.stamp = ros::Time::now();
  m.ns = "bounds";
  m.id = id;
  m.type = visualization_msgs::Marker::CUBE;

  m.scale.x = scale.x();
  m.scale.y = scale.y();
  m.scale.z = scale.z();

  m.pose.position.x = pos.x();
  m.pose.position.y = pos.y();
  m.pose.position.z = pos.z();

  m.pose.orientation.x = 0.0;
  m.pose.orientation.y = 0.0;
  m.pose.orientation.z = 0.0;
  m.pose.orientation.w = 1.0;

  m.color.r = col.r;
  m.color.g = col.g;
  m.color.b = col.b;
  m.color.a = col.a;

  pub.publish(m);

}

//==================================================================================================
//==================================================================================================
void PublishRangeMarkers(
    struct SRanges& r,
    ros::Publisher& leftMarkerPub,
    ros::Publisher& rightMarkerPub)
{

  tf::Vector3 pos;
  tf::Vector3 scale;
  struct SRgba col;

  if (leftMarkerPub.getNumSubscribers() > 0)
  {
    // Left bounds
    pos.setX((r.xLMax - r.xLMin)/2 + r.xLMin);
    pos.setY((r.yMax - r.yMin)/2 + r.yMin);
    pos.setZ((r.zMax - r.zMin)/2 + r.zMin);

    scale.setX(r.xLMax - r.xLMin);
    scale.setY(r.yMax - r.yMin);
    scale.setZ(r.zMax - r.zMin);

    // Semi-transparent blue
    col.r = 0.0f;
    col.g = 0.0f;
    col.b = 1.0f;
    col.a = 0.3f;

    PublishBoundMarker(leftMarkerPub, 1, pos, scale, col);
  }

  if (rightMarkerPub.getNumSubscribers() > 0)
  {
    // Right bounds
    pos.setX((r.xRMax - r.xRMin)/2 + r.xRMin);
    pos.setY((r.yMax - r.yMin)/2 + r.yMin);
    pos.setZ((r.zMax - r.zMin)/2 + r.zMin);

    scale.setX(r.xRMax - r.xRMin);
    scale.setY(r.yMax - r.yMin);
    scale.setZ(r.zMax - r.zMin);

    // Semi-transparent red
    col.r = 1.0f;
    col.g = 0.0f;
    col.b = 0.0f;
    col.a = 0.3f;

    PublishBoundMarker(rightMarkerPub, 2, pos, scale, col);
  }
}

//==================================================================================================
//==================================================================================================
void DriveCreate(ros::Publisher& velPub, double linear, double angular)
{
  geometry_msgs::Twist twist;
  geometry_msgs::Vector3 twistLinear;
  geometry_msgs::Vector3 twistAngular;

  twistLinear.x = linear;
  twistLinear.y = 0;
  twistLinear.z = 0;

  twistAngular.x = 0;
  twistAngular.y = 0;
  twistAngular.z = angular;

  twist.linear  = twistLinear;
  twist.angular = twistAngular;
  velPub.publish(twist);
}

//==================================================================================================
//=================================================================================================
void JoyCallback(const joy::Joy::ConstPtr& joy)
{
  linearPrev = linear;
  linear = linScale*joy->axes[1];
  angularPrev = angular;
  angular = angScale*joy->axes[0];
}

//==================================================================================================
//=================================================================================================
void ActionTimerCallback(const ros::TimerEvent& e)
{

  if(mode == create_kinect::stop)
  {
    // If in stop mode keep send stop command
    DriveCreate(velPub, 0.0f, 0.0f);
  }
  else if(mode == create_kinect::manual)
  {
    DriveCreate(velPub, linear*0.75f + linearPrev*0.25f, angular*0.75f + angularPrev*0.25f);
  }
  else if(mode == create_kinect::turnAround)
  {
    // Turn and then switch back to original mode
    DriveCreate(velPub, 0.0f, 1.5f);

    if (actionTimerCount >= 16)
    {
      // Stop before switching back
      DriveCreate(velPub, 0.0f, 0.0f);
      mode = modePrev;
    }
    else
    {
      actionTimerCount++;
    }
  }
}
//==================================================================================================
// Main
//==================================================================================================
int main (int argc, char** argv)
{
  ros::init (argc, argv, "first_test");
  ros::NodeHandle nh;

  SRanges ranges;
  DefaultRanges(ranges);

  //Do not send commands to the Create by default
  bool enableCreate = false;

  // The raw Kinect data gets rotated about the x-axis by theta radians
  // This is essentially the measure of tilt between the ground plane and the Kinect
  double theta = -0.3f;

  // This sets the forward speed of the Create
  double speed = 0.1f;

  double val;

  linear      = 0.0f;
  linearPrev  = 0.0f;
  angular     = 0.0f;
  angularPrev = 0.0f;

  angScale = 0.75;
  linScale = 0.25;

  //Used for storing pointcloud from Kinect
  CloudT cloudFull;

  //==================================== ROS Parameters ============================================

  nh.param("scale_angular", angScale, angScale);
  nh.param("scale_linear", linScale, linScale);

  // Get the Kinect rotation angle
  if (nh.getParam("/first_test/theta", val)) theta = val;

  // Get the forward speed for the create
  if (nh.getParam("/first_test/speed", val)) speed = val;

  ReadRangeParameters(nh, ranges);

  // Precomputed for efficiency
  const float cosTheta = cos(theta);
  const float sinTheta = sin(theta);

  //================================= Subscribers/publishers =======================================
  ros::Subscriber kinectSub = nh.subscribe("/camera/rgb/points", 1, CloudCallback);
  ros::Subscriber modeSub = nh.subscribe("/remote_monitor/mode", 1, ModeCallback);
  ros::Subscriber joySub = nh.subscribe<joy::Joy>("joy", 2, JoyCallback);

  ros::Publisher rotatedCloudPub = nh.advertise<sensor_msgs::PointCloud2>("rotated_cloud", 1);
  ros::Publisher leftMarkerPub   = nh.advertise<visualization_msgs::Marker>("left_slice", 1);
  ros::Publisher rightMarkerPub  = nh.advertise<visualization_msgs::Marker>("right_slice", 1);
  ros::Publisher centPub =
    nh.advertise<create_kinect::PointStatus>("/remote_monitor/pointStatus", 1);

  velPub = nh.advertise<geometry_msgs::Twist>("create_node/cmd_vel", 1);

  ros::Timer actionTimer = nh.createTimer(ros::Duration(0.1), ActionTimerCallback);

  unsigned slowCounter = 0;
  bool newData = false;

  //===================================== Main Loop ================================================
  while (nh.ok())
  {
    ros::spinOnce();
    ros::Duration(0.1).sleep();


    //Define the TF
    static tf::TransformBroadcaster br;

    tf::Transform transform;


    // Do this up to once a second
    if (slowCounter >= 9)
    {
      PublishRangeMarkers(ranges, leftMarkerPub, rightMarkerPub);
      slowCounter = 0;
    }
    else
    {
      slowCounter++;
    }

    // If no cloud received or if we have no new cloud data
    if (!cloud_ || (cloud_ == cloud_old_))
    {
      newData = false;
    }
    else
    {
      newData = true;
    }

    CloudT rotatedCloud;

    int lCount = 0;
    int rCount = 0;
    int tCount;

    float lAvgX = 0;
    float lAvgY = 0;
    float lAvgZ = 0;
    float rAvgX = 0;
    float rAvgY = 0;
    float rAvgZ = 0;

    if (newData)
    {
      // A new cloud has been received so convert the ROS message to a PointCloud<T>
      m.lock();
      {
        pcl::fromROSMsg(*cloud_, cloudFull);
      }
      m.unlock();

      // Set the old clound to make sure
      cloud_old_ = cloud_;

      for (CloudT::const_iterator it = cloudFull.begin(); it != cloudFull.end(); ++it)
      {
        // Rotate about the x-axis to align floor with xz-plane
        float x = it->x;
        float y = (it->y)*cosTheta - (it->z)*sinTheta;
        float z = (it->y)*sinTheta + (it->z)*cosTheta;

        PointT point;
        point.x = x;
        point.y = y;
        point.z = z;
        point.rgb = it->rgb;

        rotatedCloud.push_back(point);

        // Cut out points above and below vertical threshold
        if ((y > ranges.yMin) && (y < ranges.yMax))
        {
          if ((z > ranges.zMin) && (z < ranges.zMax))
          {
            if ((x < ranges.xLMax) && (x > ranges.xLMin))
            {
              lAvgX += x;
              lAvgY += y;
              lAvgZ += z;
              lCount++;
            }

            if ((x < ranges.xRMax) && (x > ranges.xRMin))
            {
              rAvgX += x;
              rAvgY += y;
              rAvgZ += z;
              rCount++;
            }
          }
        }
      }

      tCount = lCount + rCount;

      if (lCount != 0)
      {
        lAvgX = lAvgX/(float)lCount;
        lAvgY = lAvgY/(float)lCount;
        lAvgZ = lAvgZ/(float)lCount;
      }

      if (rCount != 0)
      {
        rAvgX = rAvgX/(float)rCount;
        rAvgY = rAvgY/(float)rCount;
        rAvgZ = rAvgZ/(float)rCount;
      }

      create_kinect::PointStatus ps;
      ps.centlx = lAvgX;
      ps.cently = lAvgY;
      ps.centlz = lAvgZ;
      ps.centrx = rAvgX;
      ps.centry = rAvgY;
      ps.centrz = rAvgZ;
      ps.pointCntl = lCount;
      ps.pointCntr = rCount;

      centPub.publish<create_kinect::PointStatus>(ps);

      //=================================== Point Clouds ===========================================
      sensor_msgs::PointCloud2 rotatedCloudMsg;

      pcl::toROSMsg(rotatedCloud, rotatedCloudMsg);

      transform.setOrigin(tf::Vector3(10.0,0.0,0.0));

      tf::StampedTransform trans =
        tf::StampedTransform(transform, ros::Time::now(),
        "/base_footprint",
        "/openni_camera");

      br.sendTransform(trans);

      rotatedCloudMsg.header.frame_id = "/openni_rgb_optical_frame";
      rotatedCloudMsg.header.stamp = ros::Time::now();

      rotatedCloudPub.publish(rotatedCloudMsg);
    }

    //=================================== Create Control ===========================================

    if ((mode == create_kinect::autonomous) && newData)
    {
      // If there is nothing in front go straight
      if (tCount < 1000)
      {
        DriveCreate(velPub, speed, 0.0f);
      }
      else
      {
        double angular = (float)rCount/(float)tCount - (float)lCount/(float)tCount;
        DriveCreate(velPub, speed*0.25f, angular);
      }
    }
  }

  return 0;
}
