; Auto-generated. Do not edit!


(cl:in-package hcr_vip-msg)


;//! \htmlinclude location_msg.msg.html

(cl:defclass <location_msg> (roslisp-msg-protocol:ros-message)
  ((location
    :reader location
    :initarg :location
    :type cl:string
    :initform ""))
)

(cl:defclass location_msg (<location_msg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <location_msg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'location_msg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name hcr_vip-msg:<location_msg> is deprecated: use hcr_vip-msg:location_msg instead.")))

(cl:ensure-generic-function 'location-val :lambda-list '(m))
(cl:defmethod location-val ((m <location_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hcr_vip-msg:location-val is deprecated.  Use hcr_vip-msg:location instead.")
  (location m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <location_msg>) ostream)
  "Serializes a message object of type '<location_msg>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'location))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'location))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <location_msg>) istream)
  "Deserializes a message object of type '<location_msg>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'location) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'location) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<location_msg>)))
  "Returns string type for a message object of type '<location_msg>"
  "hcr_vip/location_msg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'location_msg)))
  "Returns string type for a message object of type 'location_msg"
  "hcr_vip/location_msg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<location_msg>)))
  "Returns md5sum for a message object of type '<location_msg>"
  "03da474bc61cfeb81a8854b4ca05bafa")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'location_msg)))
  "Returns md5sum for a message object of type 'location_msg"
  "03da474bc61cfeb81a8854b4ca05bafa")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<location_msg>)))
  "Returns full string definition for message of type '<location_msg>"
  (cl:format cl:nil "string location~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'location_msg)))
  "Returns full string definition for message of type 'location_msg"
  (cl:format cl:nil "string location~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <location_msg>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'location))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <location_msg>))
  "Converts a ROS message object to a list"
  (cl:list 'location_msg
    (cl:cons ':location (location msg))
))
