; Auto-generated. Do not edit!


(cl:in-package hcr_vip-msg)


;//! \htmlinclude laser_vip.msg.html

(cl:defclass <laser_vip> (roslisp-msg-protocol:ros-message)
  ((min
    :reader min
    :initarg :min
    :type cl:float
    :initform 0.0)
   (angle_min
    :reader angle_min
    :initarg :angle_min
    :type cl:integer
    :initform 0)
   (straight
    :reader straight
    :initarg :straight
    :type cl:float
    :initform 0.0)
   (angle_straight
    :reader angle_straight
    :initarg :angle_straight
    :type cl:integer
    :initform 0)
   (right
    :reader right
    :initarg :right
    :type cl:float
    :initform 0.0)
   (angle_right
    :reader angle_right
    :initarg :angle_right
    :type cl:integer
    :initform 0)
   (left
    :reader left
    :initarg :left
    :type cl:float
    :initform 0.0)
   (angle_left
    :reader angle_left
    :initarg :angle_left
    :type cl:integer
    :initform 0))
)

(cl:defclass laser_vip (<laser_vip>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <laser_vip>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'laser_vip)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name hcr_vip-msg:<laser_vip> is deprecated: use hcr_vip-msg:laser_vip instead.")))

(cl:ensure-generic-function 'min-val :lambda-list '(m))
(cl:defmethod min-val ((m <laser_vip>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hcr_vip-msg:min-val is deprecated.  Use hcr_vip-msg:min instead.")
  (min m))

(cl:ensure-generic-function 'angle_min-val :lambda-list '(m))
(cl:defmethod angle_min-val ((m <laser_vip>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hcr_vip-msg:angle_min-val is deprecated.  Use hcr_vip-msg:angle_min instead.")
  (angle_min m))

(cl:ensure-generic-function 'straight-val :lambda-list '(m))
(cl:defmethod straight-val ((m <laser_vip>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hcr_vip-msg:straight-val is deprecated.  Use hcr_vip-msg:straight instead.")
  (straight m))

(cl:ensure-generic-function 'angle_straight-val :lambda-list '(m))
(cl:defmethod angle_straight-val ((m <laser_vip>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hcr_vip-msg:angle_straight-val is deprecated.  Use hcr_vip-msg:angle_straight instead.")
  (angle_straight m))

(cl:ensure-generic-function 'right-val :lambda-list '(m))
(cl:defmethod right-val ((m <laser_vip>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hcr_vip-msg:right-val is deprecated.  Use hcr_vip-msg:right instead.")
  (right m))

(cl:ensure-generic-function 'angle_right-val :lambda-list '(m))
(cl:defmethod angle_right-val ((m <laser_vip>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hcr_vip-msg:angle_right-val is deprecated.  Use hcr_vip-msg:angle_right instead.")
  (angle_right m))

(cl:ensure-generic-function 'left-val :lambda-list '(m))
(cl:defmethod left-val ((m <laser_vip>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hcr_vip-msg:left-val is deprecated.  Use hcr_vip-msg:left instead.")
  (left m))

(cl:ensure-generic-function 'angle_left-val :lambda-list '(m))
(cl:defmethod angle_left-val ((m <laser_vip>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hcr_vip-msg:angle_left-val is deprecated.  Use hcr_vip-msg:angle_left instead.")
  (angle_left m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <laser_vip>) ostream)
  "Serializes a message object of type '<laser_vip>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'min))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'angle_min)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'straight))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'angle_straight)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'right))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'angle_right)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'left))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'angle_left)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <laser_vip>) istream)
  "Deserializes a message object of type '<laser_vip>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'min) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'angle_min) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'straight) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'angle_straight) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'right) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'angle_right) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'left) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'angle_left) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<laser_vip>)))
  "Returns string type for a message object of type '<laser_vip>"
  "hcr_vip/laser_vip")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'laser_vip)))
  "Returns string type for a message object of type 'laser_vip"
  "hcr_vip/laser_vip")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<laser_vip>)))
  "Returns md5sum for a message object of type '<laser_vip>"
  "e73dc269eca68298ea43af26934ac6d0")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'laser_vip)))
  "Returns md5sum for a message object of type 'laser_vip"
  "e73dc269eca68298ea43af26934ac6d0")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<laser_vip>)))
  "Returns full string definition for message of type '<laser_vip>"
  (cl:format cl:nil "float64 min~%int32 angle_min~%float64 straight~%int32 angle_straight~%float64 right~%int32 angle_right~%float64 left~%int32 angle_left~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'laser_vip)))
  "Returns full string definition for message of type 'laser_vip"
  (cl:format cl:nil "float64 min~%int32 angle_min~%float64 straight~%int32 angle_straight~%float64 right~%int32 angle_right~%float64 left~%int32 angle_left~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <laser_vip>))
  (cl:+ 0
     8
     4
     8
     4
     8
     4
     8
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <laser_vip>))
  "Converts a ROS message object to a list"
  (cl:list 'laser_vip
    (cl:cons ':min (min msg))
    (cl:cons ':angle_min (angle_min msg))
    (cl:cons ':straight (straight msg))
    (cl:cons ':angle_straight (angle_straight msg))
    (cl:cons ':right (right msg))
    (cl:cons ':angle_right (angle_right msg))
    (cl:cons ':left (left msg))
    (cl:cons ':angle_left (angle_left msg))
))
