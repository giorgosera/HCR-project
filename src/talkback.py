#!/usr/bin/env python

"""
    talkback.py - Say back what is heard by the pocketsphinx recognizer.
"""

import roslib; roslib.load_manifest('hcr_vip')
import rospy
import sys
from hcr_vip.msg import sensorMsg
from string import Template 

from sound_play.libsoundplay import SoundClient

################################################
# GLOBALS
###############################################

type_danger = {"warning": {"speech":"Warning. Distance %5s angle %5s", 
			   "non-speech":"/sssmalert.wav"}, 
	       "danger": {"speech":"Danger. Distance %5s angle %5s",
			  "non-speech":"/BEEP2.WAV"}, 
	       "immediate danger": {"speech":"Immediate danger. Distance %5s angle %5s",
				    "non-speech":"/BEEP2.WAV"}}

class TalkBack:
    def __init__(self, mode):
        rospy.on_shutdown(self.cleanup)
	rospy.loginfo("Initialising node...")
          
        self.voice = "voice_cmu_us_clb_arctic_clunits"
	#self.rate = rospy.Rate(0.5)        
	self.wavepath = "/home/robofriend/ros_workspace/hcr_vip/sounds"
	self.mode = mode

	# Create the sound client object
        self.soundhandle = SoundClient()	    

        rospy.sleep(1)
        self.soundhandle.stopAll()

        # Subscribe to the recognizer output
        try:
	    rospy.loginfo("Subsribing  to the topic...")	
    	    #rospy.Subscriber("SensorMsg", sensorMsg, self.talkback)
            rospy.Subscriber("mockMasterTopic", sensorMsg, self.talkback)	
	except Exception, e:
	    print e
        rospy.loginfo("Subscribed  to the topic...")

    def talkback(self, msg):
        # Print the recognized words on the screen
	rospy.loginfo("-----------------------")
	rospy.loginfo("Processing messages...")
	distance = str(msg.range)
	angle = str(msg.angle)
	
	rospy.loginfo("Distance:"+distance)
	rospy.loginfo("Angle:"+angle)
	
	if distance > 5.0:
	    print "warn"
	    msg = type_danger["warning"]
	elif distance > 1.0:
       	    msg = type_danger["danger"]
	else:
	    msg = type_danger["immediate danger"]

	try:
   	    if self.mode == "speech":
                rospy.sleep(3) 
	        self.soundhandle.say(msg["speech"]%(distance,angle), self.voice)
	    else:
		rospy.sleep(1)
		self.soundhandle.playWave(self.wavepath + msg["non-speech"])
		rospy.sleep(1)
	except Exception, e:
	    print e
	
        self.soundhandle.stopAll()	

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

