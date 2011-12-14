#!/usr/bin/env python

"""
    talkback.py - Say back what is heard by the pocketsphinx recognizer.
"""

import roslib; roslib.load_manifest('hcr_vip')
import rospy
import sys
import math
from hcr_vip.msg import sensorMsg
from string import Template 

from sound_play.libsoundplay import SoundClient

################################################
# GLOBALS
###############################################

type_danger = {"warning": {"speech":"WARNING. %10s meters %10s", 
			   "non-speech":"/sssmalert.wav"}, 
	       "danger": {"speech":"Danger. %10s meters %10s",
			  "non-speech":"/DingLing.wav"}, 
	       "immediate danger": {"speech":"Immediate danger. %10s meters %10s",
				    "non-speech":"/DINGING.WAV"}}

config = {"wavepath":"/home/robofriend/ros_workspace/hcr_vip/sounds",
	  "voice":"voice_cmu_us_clb_arctic_clunits",
	  "topic": {"name":"mockMasterTopic", "msg_type":sensorMsg}}
	  #"topic": {"name":"SensorMsg", "msg_type":sensorMsg}}

class TalkBack:
    def __init__(self, mode):
        rospy.on_shutdown(self.cleanup)
	rospy.loginfo("Initialising node...")
          
        self.voice = config["voice"]  
	self.wavepath = config["wavepath"]
	self.mode = mode
	self.last_obstacle = ("0.0", "0")
	# Create the sound client object
        self.soundhandle = SoundClient()	    
        rospy.sleep(1)
        self.soundhandle.stopAll()

        # Subscribe to the sensor output
        try:
	    rospy.loginfo("Subsribing  to the topic...")	
            rospy.Subscriber(config["topic"]["name"], config["topic"]["msg_type"], self.talkback)	
	except Exception, e:
	    print e
        rospy.loginfo("Subscribed  to the topic...")

    def talkback(self, msg):
        #Print the recognized words on the screen
	rospy.loginfo("-----------------------")
	rospy.loginfo("Processing messages...")

	distance = str(round(msg.range, 1))
	angle = str(msg.angle)
	msg = self._get_danger_message(distance)	
	direction = self._get_danger_direction(angle)
	
	#We calculate the displacement since last message. If within a 
	# threshold then don't issue a message.
	distance_diff = float(self.last_obstacle[0]) - float(distance)
        angle_diff = int(self.last_obstacle[1]) - int(angle)

  	if math.fabs(distance_diff) > 0.1 and  math.fabs(angle_diff) > 5:
	    try:
   	    	if self.mode == "speech": 
	            self.soundhandle.say(msg["speech"]%(distance,direction), self.voice)
		    rospy.sleep(2.5)
	    	else:
		    rospy.sleep(1)
	            self.soundhandle.playWave(self.wavepath + msg["non-speech"])
		    rospy.sleep(1)
	    except Exception, e:
	        print e
	    
	    self.last_obstacle = (distance, angle)
	else:
	     rospy.loginfo("Skipping message. Nothing really changed since last message.")
	     self.last_obstacle = (distance, angle)
	
	rospy.loginfo("Distance:"+distance)
        rospy.loginfo("Angle:"+angle)
        rospy.loginfo("Direction of danger:"+direction)

        self.soundhandle.stopAll()	

    def _get_danger_message(self, distance):
	'''
	Returns the type of danger depending on the distance from the closest obsracle
	It's supposed to be a private method. Should not be called from outside
	'''	
	if float(distance) > 1.5:
            msg = type_danger["warning"]
        elif float(distance) > 1.0:
            msg = type_danger["danger"]
        else:
            msg = type_danger["immediate danger"]
	return msg

    def _get_danger_direction(self, angle):
	div_angle = int(angle)/45
	if div_angle in [0, 7]:
	    direction = "front"
	elif div_angle in [1, 2]:
	    direction = "right"
	elif div_angle in [5, 6]:
	    direction = "left"
	else:
	    direction = "behind"
	   
	return direction
	
    def cleanup(self):
	self.soundhandle.stopAll()
        rospy.loginfo("Shutting down talkback node...")

if __name__=="__main__":
    try:
	if len(sys.argv) == 1:
	    mode = sys.stdin.read()
	else:
	    mode = sys.argv[1]
            if mode not in ['speech', 'non-speech']:
		print mode," is not a recognised command line argument. Either use speech or non-speech"
		raise TypeError("Not recognised command line argument")
	rospy.init_node('talkback', anonymous=True)
	TalkBack(mode)
	rospy.spin()
	print "After spin"
    except:
        pass

