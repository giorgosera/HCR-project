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
################################################

type_danger = {"info":    {"speech":"Info. %10s %10s", 
			   "non-speech":"/sssmalert.wav"}, 
	       "warning": {"speech":"Warning. %10s %10s",
			  "non-speech":"/DingLing.wav"}, 
	       "danger":  {"speech":"Danger. %10s",
		           "non-speech":"/DINGING.WAV"}}

config = {"wavepath":"/home/robofriend/ros_workspace/hcr_vip/sounds",
	  "voice":"voice_cmu_us_clb_arctic_clunits",
	  #"topic": {"name":"mockMasterTopic", "msg_type":sensorMsg}}
	  #"topic": {"name":"SensorMsg", "msg_type":sensorMsg}}
	  "topic": {"name":"WarningMsg", "msg_type":sensorMsg}}

class TalkBack:
    def __init__(self, mode):
        rospy.on_shutdown(self.cleanup)
	rospy.loginfo("Initialising node...")
          
        self.voice = config["voice"]  
	self.wavepath = config["wavepath"]
	self.mode = mode
	self.last_obstacle = ("0.0", "0")
	self.last_direction = "unknown"
	self.msg_count = 0

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
	rospy.loginfo("Processing message...")

	distance = str(round(msg.range, 1))
	angle = str(msg.angle)
        direction = self._get_danger_direction(angle)
	msg, type = self._get_danger_message(distance, direction, mode)	
	
	if float(distance) >= 0 and direction != "behind" and self.msg_count >= 20:
	    try:
		rospy.loginfo("COMMUNICATING MESSAGE.")
   	    	if self.mode == "speech":
		    self.soundhandle.say(msg, self.voice)
 		    rospy.sleep(1)
	    	else:
	            self.soundhandle.playWave(self.wavepath + msg)
		    rospy.sleep(1.5)
	    except Exception, e:
	        print e
	    self.msg_count = 0
	else:
	     self.msg_count += 1	 
	     rospy.loginfo("SKIPPING MESSAGE.")
	
        self._print_log_info(distance, angle, direction, type)
        self.soundhandle.stopAll()	
	
    def _print_log_info(self, distance, angle, direction, type):
	'''
	Reports log information for this iteration. Private method.
        '''
        rospy.loginfo("Distance:" + distance)
        rospy.loginfo("Angle:" + angle)
        rospy.loginfo("Direction of danger:"+direction)
        rospy.loginfo("Type of danger:"+type)
        rospy.loginfo("Msgs received so far:"+str(self.msg_count))

    def _get_danger_message(self, distance, direction, mode):
	'''
	Returns the type of danger depending on the distance from the closest obsracle
	It's supposed to be a private method. Should not be called from outside
	'''	
	#If it's in speech mode we want to append some variables to
        #the template string. Otherwise no need to do that 
	if mode == "speech":	
	    template_str = (int(float(distance)),direction)
	else:
	    template_str = ()	
        
	if float(distance) > 1.2:
	    if mode == "speech":
            	msg = type_danger["info"][mode]%template_str
	    else:
	        msg = type_danger["info"][mode]
	    type = "info"
        elif float(distance) > 1.0:
            if mode == "speech":
                msg = type_danger["warning"][mode]%template_str
            else:
                msg = type_danger["warning"][mode]  
	    type = "warning"
        else:
	    template_str = direction
            if mode == "speech":
                msg = type_danger["danger"][mode]%template_str
            else:
                msg = type_danger["danger"][mode]  
	    type = "danger"
	return msg, type

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
    except:
        pass

