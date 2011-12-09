#!/usr/bin/env python

"""
    talkback.py - Say back what is heard by the pocketsphinx recognizer.
"""

import roslib; roslib.load_manifest('hcr_vip')
import rospy
from hcr_vip.msg import laser_vip

from sound_play.libsoundplay import SoundClient

class TalkBack:
    def __init__(self):
        rospy.on_shutdown(self.cleanup)
	rospy.loginfo("Initialising node...")
          
        self.voice = "voice_cmu_us_clb_arctic_clunits"
	self.rate = rospy.Rate(0.5)        
	# Create the sound client object
        self.soundhandle = SoundClient()
       
        rospy.sleep(1)
        self.soundhandle.stopAll()
        # Subscribe to the recognizer output
        try:
	    rospy.loginfo("Subsribing  to the topic...")	
    	    rospy.Subscriber("laser_vip", laser_vip, self.talkback)
        except Exception, e:
	    print e
        rospy.loginfo("Subscribed  to the topic...")

    def talkback(self, msg):
        # Print the recognized words on the screen
        rospy.loginfo("Processing messages...")
	msg = msg.angle_min
	#rospy.sleep(2)
	self.rate.sleep()
	self.soundhandle.say(str(msg), self.voice)
	rospy.loginfo(msg)
        self.soundhandle.stopAll()	

    def cleanup(self):
        rospy.loginfo("Shutting down talkback node...")

if __name__=="__main__":
    try:
        rospy.init_node('talkback', anonymous=True)
	TalkBack()
	rospy.spin()
    except:
        pass

