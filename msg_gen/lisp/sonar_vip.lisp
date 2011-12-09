; Auto-generated. Do not edit!


(cl:in-package hcr_vip-msg)


;//! \htmlinclude sonar_vip.msg.html

(cl:defclass <sonar_vip> (roslisp-msg-protocol:ros-message)
  ((distance_front
    :reader distance_front
    :initarg :distance_front
    :type cl:float
    :initform 0.0)
   (angle_front
    :reader angle_front
    :initarg :angle_front
    :type cl:integer
    :initform 0)
   (distance_back
    :reader distance_back
    :initarg :distance_back
    :type cl:float
    :initform 0.0)
   (angle_back
    :reader angle_back
    :initarg :angle_back
    :type cl:integer
    :initform 0)
   (turn_left
    :reader turn_left
    :initarg :turn_left
    :type cl:float
    :initform 0.0)
   (turn_left_sensor
    :reader turn_left_sensor
    :initarg :turn_left_sensor
    :type cl:string
    :initform "")
   (turn_right
    :reader turn_right
    :initarg :turn_right
    :type cl:float
    :initform 0.0)
   (turn_right_sensor
    :reader turn_right_sensor
    :initarg :turn_right_sensor
    :type cl:string
    :initform ""))
)

(cl:defclass sonar_vip (<sonar_vip>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <sonar_vip>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'sonar_vip)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name hcr_vip-msg:<sonar_vip> is deprecated: use hcr_vip-msg:sonar_vip instead.")))

(cl:ensure-generic-function 'distance_front-val :lambda-list '(m))
(cl:defmethod distance_front-val ((m <sonar_vip>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hcr_vip-msg:distance_front-val is deprecated.  Use hcr_vip-msg:distance_front instead.")
  (distance_front m))

(cl:ensure-generic-function 'angle_front-val :lambda-list '(m))
(cl:defmethod angle_front-val ((m <sonar_vip>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hcr_vip-msg:angle_front-val is deprecated.  Use hcr_vip-msg:angle_front instead.")
  (angle_front m))

(cl:ensure-generic-function 'distance_back-val :lambda-list '(m))
(cl:defmethod distance_back-val ((m <sonar_vip>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hcr_vip-msg:distance_back-val is deprecated.  Use hcr_vip-msg:distance_back instead.")
  (distance_back m))

(cl:ensure-generic-function 'angle_back-val :lambda-list '(m))
(cl:defmethod angle_back-val ((m <sonar_vip>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hcr_vip-msg:angle_back-val is deprecated.  Use hcr_vip-msg:angle_back instead.")
  (angle_back m))

(cl:ensure-generic-function 'turn_left-val :lambda-list '(m))
(cl:defmethod turn_left-val ((m <sonar_vip>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hcr_vip-msg:turn_left-val is deprecated.  Use hcr_vip-msg:turn_left instead.")
  (turn_left m))

(cl:ensure-generic-function 'turn_left_sensor-val :lambda-list '(m))
(cl:defmethod turn_left_sensor-val ((m <sonar_vip>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hcr_vip-msg:turn_left_sensor-val is deprecated.  Use hcr_vip-msg:turn_left_sensor instead.")
  (turn_left_sensor m))

(cl:ensure-generic-function 'turn_right-val :lambda-list '(m))
(cl:defmethod turn_right-val ((m <sonar_vip>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hcr_vip-msg:turn_right-val is deprecated.  Use hcr_vip-msg:turn_right instead.")
  (turn_right m))

(cl:ensure-generic-function 'turn_right_sensor-val :lambda-list '(m))
(cl:defmethod turn_right_sensor-val ((m <sonar_vip>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hcr_vip-msg:turn_right_sensor-val is deprecated.  Use hcr_vip-msg:turn_right_sensor instead.")
  (turn_right_sensor m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <sonar_vip>) ostream)
  "Serializes a message object of type '<sonar_vip>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'distance_front))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'angle_front)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'distance_back))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'angle_back)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'turn_left))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'turn_left_sensor))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'turn_left_sensor))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'turn_right))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'turn_right_sensor))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'turn_right_sensor))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <sonar_vip>) istream)
  "Deserializes a message object of type '<sonar_vip>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'distance_front) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'angle_front) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'distance_back) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'angle_back) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'turn_left) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'turn_left_sensor) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'turn_left_sensor) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'turn_right) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'turn_right_sensor) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'turn_right_sensor) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<sonar_vip>)))
  "Returns string type for a message object of type '<sonar_vip>"
  "hcr_vip/sonar_vip")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'sonar_vip)))
  "Returns string type for a message object of type 'sonar_vip"
  "hcr_vip/sonar_vip")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<sonar_vip>)))
  "Returns md5sum for a message object of type '<sonar_vip>"
  "ee8100ffc8e6dc1410f852f63a502f01")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'sonar_vip)))
  "Returns md5sum for a message object of type 'sonar_vip"
  "ee8100ffc8e6dc1410f852f63a502f01")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<sonar_vip>)))
  "Returns full string definition for message of type '<sonar_vip>"
  (cl:format cl:nil "float64 distance_front~%int32 angle_front~%float64 distance_back~%int32 angle_back~%float64 turn_left~%string turn_left_sensor~%float64 turn_right~%string turn_right_sensor~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'sonar_vip)))
  "Returns full string definition for message of type 'sonar_vip"
  (cl:format cl:nil "float64 distance_front~%int32 angle_front~%float64 distance_back~%int32 angle_back~%float64 turn_left~%string turn_left_sensor~%float64 turn_right~%string turn_right_sensor~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <sonar_vip>))
  (cl:+ 0
     8
     4
     8
     4
     8
     4 (cl:length (cl:slot-value msg 'turn_left_sensor))
     8
     4 (cl:length (cl:slot-value msg 'turn_right_sensor))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <sonar_vip>))
  "Converts a ROS message object to a list"
  (cl:list 'sonar_vip
    (cl:cons ':distance_front (distance_front msg))
    (cl:cons ':angle_front (angle_front msg))
    (cl:cons ':distance_back (distance_back msg))
    (cl:cons ':angle_back (angle_back msg))
    (cl:cons ':turn_left (turn_left msg))
    (cl:cons ':turn_left_sensor (turn_left_sensor msg))
    (cl:cons ':turn_right (turn_right msg))
    (cl:cons ':turn_right_sensor (turn_right_sensor msg))
))
