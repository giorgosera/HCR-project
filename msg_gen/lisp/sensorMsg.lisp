; Auto-generated. Do not edit!


(cl:in-package hcr_vip-msg)


;//! \htmlinclude sensorMsg.msg.html

(cl:defclass <sensorMsg> (roslisp-msg-protocol:ros-message)
  ((range
    :reader range
    :initarg :range
    :type cl:float
    :initform 0.0)
   (angle
    :reader angle
    :initarg :angle
    :type cl:integer
    :initform 0))
)

(cl:defclass sensorMsg (<sensorMsg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <sensorMsg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'sensorMsg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name hcr_vip-msg:<sensorMsg> is deprecated: use hcr_vip-msg:sensorMsg instead.")))

(cl:ensure-generic-function 'range-val :lambda-list '(m))
(cl:defmethod range-val ((m <sensorMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hcr_vip-msg:range-val is deprecated.  Use hcr_vip-msg:range instead.")
  (range m))

(cl:ensure-generic-function 'angle-val :lambda-list '(m))
(cl:defmethod angle-val ((m <sensorMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hcr_vip-msg:angle-val is deprecated.  Use hcr_vip-msg:angle instead.")
  (angle m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <sensorMsg>) ostream)
  "Serializes a message object of type '<sensorMsg>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'range))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'angle)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <sensorMsg>) istream)
  "Deserializes a message object of type '<sensorMsg>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'range) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'angle) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<sensorMsg>)))
  "Returns string type for a message object of type '<sensorMsg>"
  "hcr_vip/sensorMsg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'sensorMsg)))
  "Returns string type for a message object of type 'sensorMsg"
  "hcr_vip/sensorMsg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<sensorMsg>)))
  "Returns md5sum for a message object of type '<sensorMsg>"
  "94e4ddec41eacd305c0c6884f02179d8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'sensorMsg)))
  "Returns md5sum for a message object of type 'sensorMsg"
  "94e4ddec41eacd305c0c6884f02179d8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<sensorMsg>)))
  "Returns full string definition for message of type '<sensorMsg>"
  (cl:format cl:nil "float64 range~%int32 angle~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'sensorMsg)))
  "Returns full string definition for message of type 'sensorMsg"
  (cl:format cl:nil "float64 range~%int32 angle~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <sensorMsg>))
  (cl:+ 0
     8
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <sensorMsg>))
  "Converts a ROS message object to a list"
  (cl:list 'sensorMsg
    (cl:cons ':range (range msg))
    (cl:cons ':angle (angle msg))
))
