/* Auto-generated by genmsg_cpp for file /home/robofriend/ros_workspace/hcr_vip/msg/laser_vip.msg */
#ifndef HCR_VIP_MESSAGE_LASER_VIP_H
#define HCR_VIP_MESSAGE_LASER_VIP_H
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/time.h"

#include "ros/macros.h"

#include "ros/assert.h"


namespace hcr_vip
{
template <class ContainerAllocator>
struct laser_vip_ {
  typedef laser_vip_<ContainerAllocator> Type;

  laser_vip_()
  : min(0.0)
  , angle_min(0)
  , straight(0.0)
  , angle_straight(0)
  , right(0.0)
  , angle_right(0)
  , left(0.0)
  , angle_left(0)
  {
  }

  laser_vip_(const ContainerAllocator& _alloc)
  : min(0.0)
  , angle_min(0)
  , straight(0.0)
  , angle_straight(0)
  , right(0.0)
  , angle_right(0)
  , left(0.0)
  , angle_left(0)
  {
  }

  typedef double _min_type;
  double min;

  typedef int32_t _angle_min_type;
  int32_t angle_min;

  typedef double _straight_type;
  double straight;

  typedef int32_t _angle_straight_type;
  int32_t angle_straight;

  typedef double _right_type;
  double right;

  typedef int32_t _angle_right_type;
  int32_t angle_right;

  typedef double _left_type;
  double left;

  typedef int32_t _angle_left_type;
  int32_t angle_left;


private:
  static const char* __s_getDataType_() { return "hcr_vip/laser_vip"; }
public:
  ROS_DEPRECATED static const std::string __s_getDataType() { return __s_getDataType_(); }

  ROS_DEPRECATED const std::string __getDataType() const { return __s_getDataType_(); }

private:
  static const char* __s_getMD5Sum_() { return "e73dc269eca68298ea43af26934ac6d0"; }
public:
  ROS_DEPRECATED static const std::string __s_getMD5Sum() { return __s_getMD5Sum_(); }

  ROS_DEPRECATED const std::string __getMD5Sum() const { return __s_getMD5Sum_(); }

private:
  static const char* __s_getMessageDefinition_() { return "float64 min\n\
int32 angle_min\n\
float64 straight\n\
int32 angle_straight\n\
float64 right\n\
int32 angle_right\n\
float64 left\n\
int32 angle_left\n\
\n\
\n\
"; }
public:
  ROS_DEPRECATED static const std::string __s_getMessageDefinition() { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED const std::string __getMessageDefinition() const { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED virtual uint8_t *serialize(uint8_t *write_ptr, uint32_t seq) const
  {
    ros::serialization::OStream stream(write_ptr, 1000000000);
    ros::serialization::serialize(stream, min);
    ros::serialization::serialize(stream, angle_min);
    ros::serialization::serialize(stream, straight);
    ros::serialization::serialize(stream, angle_straight);
    ros::serialization::serialize(stream, right);
    ros::serialization::serialize(stream, angle_right);
    ros::serialization::serialize(stream, left);
    ros::serialization::serialize(stream, angle_left);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint8_t *deserialize(uint8_t *read_ptr)
  {
    ros::serialization::IStream stream(read_ptr, 1000000000);
    ros::serialization::deserialize(stream, min);
    ros::serialization::deserialize(stream, angle_min);
    ros::serialization::deserialize(stream, straight);
    ros::serialization::deserialize(stream, angle_straight);
    ros::serialization::deserialize(stream, right);
    ros::serialization::deserialize(stream, angle_right);
    ros::serialization::deserialize(stream, left);
    ros::serialization::deserialize(stream, angle_left);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint32_t serializationLength() const
  {
    uint32_t size = 0;
    size += ros::serialization::serializationLength(min);
    size += ros::serialization::serializationLength(angle_min);
    size += ros::serialization::serializationLength(straight);
    size += ros::serialization::serializationLength(angle_straight);
    size += ros::serialization::serializationLength(right);
    size += ros::serialization::serializationLength(angle_right);
    size += ros::serialization::serializationLength(left);
    size += ros::serialization::serializationLength(angle_left);
    return size;
  }

  typedef boost::shared_ptr< ::hcr_vip::laser_vip_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::hcr_vip::laser_vip_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct laser_vip
typedef  ::hcr_vip::laser_vip_<std::allocator<void> > laser_vip;

typedef boost::shared_ptr< ::hcr_vip::laser_vip> laser_vipPtr;
typedef boost::shared_ptr< ::hcr_vip::laser_vip const> laser_vipConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::hcr_vip::laser_vip_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::hcr_vip::laser_vip_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace hcr_vip

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::hcr_vip::laser_vip_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::hcr_vip::laser_vip_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::hcr_vip::laser_vip_<ContainerAllocator> > {
  static const char* value() 
  {
    return "e73dc269eca68298ea43af26934ac6d0";
  }

  static const char* value(const  ::hcr_vip::laser_vip_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0xe73dc269eca68298ULL;
  static const uint64_t static_value2 = 0xea43af26934ac6d0ULL;
};

template<class ContainerAllocator>
struct DataType< ::hcr_vip::laser_vip_<ContainerAllocator> > {
  static const char* value() 
  {
    return "hcr_vip/laser_vip";
  }

  static const char* value(const  ::hcr_vip::laser_vip_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::hcr_vip::laser_vip_<ContainerAllocator> > {
  static const char* value() 
  {
    return "float64 min\n\
int32 angle_min\n\
float64 straight\n\
int32 angle_straight\n\
float64 right\n\
int32 angle_right\n\
float64 left\n\
int32 angle_left\n\
\n\
\n\
";
  }

  static const char* value(const  ::hcr_vip::laser_vip_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::hcr_vip::laser_vip_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::hcr_vip::laser_vip_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.min);
    stream.next(m.angle_min);
    stream.next(m.straight);
    stream.next(m.angle_straight);
    stream.next(m.right);
    stream.next(m.angle_right);
    stream.next(m.left);
    stream.next(m.angle_left);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct laser_vip_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::hcr_vip::laser_vip_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::hcr_vip::laser_vip_<ContainerAllocator> & v) 
  {
    s << indent << "min: ";
    Printer<double>::stream(s, indent + "  ", v.min);
    s << indent << "angle_min: ";
    Printer<int32_t>::stream(s, indent + "  ", v.angle_min);
    s << indent << "straight: ";
    Printer<double>::stream(s, indent + "  ", v.straight);
    s << indent << "angle_straight: ";
    Printer<int32_t>::stream(s, indent + "  ", v.angle_straight);
    s << indent << "right: ";
    Printer<double>::stream(s, indent + "  ", v.right);
    s << indent << "angle_right: ";
    Printer<int32_t>::stream(s, indent + "  ", v.angle_right);
    s << indent << "left: ";
    Printer<double>::stream(s, indent + "  ", v.left);
    s << indent << "angle_left: ";
    Printer<int32_t>::stream(s, indent + "  ", v.angle_left);
  }
};


} // namespace message_operations
} // namespace ros

#endif // HCR_VIP_MESSAGE_LASER_VIP_H
