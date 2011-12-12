#!/usr/bin/env python

"""
    talkback.py - Say back what is heard by the pocketsphinx recognizer.
"""

import roslib; roslib.load_manifest('hcr_vip')
import rospy
import sys
from hcr_vip.msg import sensorMsg

from sound_play.libsoundplay import SoundClient

class TalkBack:
    def __init__(self, mode):
        rospy.on_shutdown(self.cleanup)
	rospy.loginfo("Initialising node...")
          
        self.voice = "voice_cmu_us_clb_arctic_clunits"
	self.rate = rospy.Rate(0.5)        
	self.wavepath = "/home/robofriend/ros_workspace/hcr_vip/sounds/sssmalert.wav"
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
	rospy.loginfo("Processing messages...")
	msg = msg.range
	rospy.sleep(0.001)
	#self.rate.sleep()	
	try:
   	    if self.mode == "speech":
	        self.soundhandle.say(str(msg), self.voice)
	    else:
		rospy.sleep(1)
   	        self.soundhandle.playWave(self.wavepath)
		rospy.sleep(1)
	except Exception, e:
	    print e

	rospy.loginfo(msg)
        self.soundhandle.stopAll()	

    def cleanup(self):
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

