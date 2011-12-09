rosrun ROSARIA RosAria
rosparam set joy_node/dev "/dev/input/js1"
rosrun joy joy_node
rosrun hcr_vip JoyStickControllerWithSonar
rosrun hcr_vip Sonar

rosrun sicktoolbox_wrapper sicklms _port:="/dev/ttyUSB1" _baud:=38400