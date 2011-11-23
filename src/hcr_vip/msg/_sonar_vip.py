"""autogenerated by genmsg_py from sonar_vip.msg. Do not edit."""
import roslib.message
import struct


class sonar_vip(roslib.message.Message):
  _md5sum = "88e0f89c92fb21e7f26144ddd9a139a3"
  _type = "hcr_vip/sonar_vip"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """float64 distance_front
int32 angle_front
float64 distance_back
int32 angle_back
float64 turn_left
float64 turn_right


"""
  __slots__ = ['distance_front','angle_front','distance_back','angle_back','turn_left','turn_right']
  _slot_types = ['float64','int32','float64','int32','float64','float64']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.
    
    The available fields are:
       distance_front,angle_front,distance_back,angle_back,turn_left,turn_right
    
    @param args: complete set of field values, in .msg order
    @param kwds: use keyword arguments corresponding to message field names
    to set specific fields. 
    """
    if args or kwds:
      super(sonar_vip, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.distance_front is None:
        self.distance_front = 0.
      if self.angle_front is None:
        self.angle_front = 0
      if self.distance_back is None:
        self.distance_back = 0.
      if self.angle_back is None:
        self.angle_back = 0
      if self.turn_left is None:
        self.turn_left = 0.
      if self.turn_right is None:
        self.turn_right = 0.
    else:
      self.distance_front = 0.
      self.angle_front = 0
      self.distance_back = 0.
      self.angle_back = 0
      self.turn_left = 0.
      self.turn_right = 0.

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    @param buff: buffer
    @type  buff: StringIO
    """
    try:
      _x = self
      buff.write(_struct_didi2d.pack(_x.distance_front, _x.angle_front, _x.distance_back, _x.angle_back, _x.turn_left, _x.turn_right))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    @param str: byte array of serialized message
    @type  str: str
    """
    try:
      end = 0
      _x = self
      start = end
      end += 40
      (_x.distance_front, _x.angle_front, _x.distance_back, _x.angle_back, _x.turn_left, _x.turn_right,) = _struct_didi2d.unpack(str[start:end])
      return self
    except struct.error as e:
      raise roslib.message.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    @param buff: buffer
    @type  buff: StringIO
    @param numpy: numpy python module
    @type  numpy module
    """
    try:
      _x = self
      buff.write(_struct_didi2d.pack(_x.distance_front, _x.angle_front, _x.distance_back, _x.angle_back, _x.turn_left, _x.turn_right))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    @param str: byte array of serialized message
    @type  str: str
    @param numpy: numpy python module
    @type  numpy: module
    """
    try:
      end = 0
      _x = self
      start = end
      end += 40
      (_x.distance_front, _x.angle_front, _x.distance_back, _x.angle_back, _x.turn_left, _x.turn_right,) = _struct_didi2d.unpack(str[start:end])
      return self
    except struct.error as e:
      raise roslib.message.DeserializationError(e) #most likely buffer underfill

_struct_I = roslib.message.struct_I
_struct_didi2d = struct.Struct("<didi2d")
