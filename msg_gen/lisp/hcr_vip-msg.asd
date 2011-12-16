
(cl:in-package :asdf)

(defsystem "hcr_vip-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "location_msg" :depends-on ("_package_location_msg"))
    (:file "_package_location_msg" :depends-on ("_package"))
    (:file "laser_vip" :depends-on ("_package_laser_vip"))
    (:file "_package_laser_vip" :depends-on ("_package"))
    (:file "sonar_vip" :depends-on ("_package_sonar_vip"))
    (:file "_package_sonar_vip" :depends-on ("_package"))
    (:file "sensorMsg" :depends-on ("_package_sensorMsg"))
    (:file "_package_sensorMsg" :depends-on ("_package"))
  ))