rosrun ROSARIA RosAria
rosparam set joy_node/dev "/dev/input/js1"
rosrun joy joy_node
rosrun hcr_vip JoyStickControllerWithSonar
rosrun hcr_vip Sonar

rosrun sicktoolbox_wrapper sicklms _port:="/dev/ttyUSB1" _baud:=38400

How to run speech synthesis:
-----------------------------

1) rosrun sound_play sound_playnode.py
2) rosrun hcr_vip talkback.py

***Warning***
Run soundplay node on the robot's laptop NOT on yours.
Otherwise sound is not redirected to Jabra Wave

How to run speech recognition:
-----------------------------
1) roslaunch hcr_vip voice_nav_commands.launch
2) roslaunch hcr_vip location_recogniser.launch 

