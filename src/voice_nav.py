#!/usr/bin/env python

"""
  voice_nav.py allows controlling a mobile base using simple speech commands.
  Based on the voice_cmd_vel.py script by Michael Ferguson in the pocketsphinx ROS package.
"""

import roslib; roslib.load_manifest('hcr_vip')
import rospy
from hcr_vip.msg import location_msg
from std_msgs.msg import String

class LocationRecogniser:
    def __init__(self):
        rospy.on_shutdown(self.cleanup)
        self.rate = rospy.get_param("~rate", 5)
        r = rospy.Rate(self.rate)

        # Initialize the String message we will publish.
	self.msg = String()
        
        # Publish the Twist message to the cmd_vel topic
        self.location_pub = rospy.Publisher('locationTopic', String)
	 
        # Subscribe to the /recognizer/output topic to receive voice commands.
        try:
   	     rospy.Subscriber('/recognizer/output', String, self.callback)
        except Exception, e:
	    print e
        # A mapping from keywords to commands.
        self.keywords_to_command = {'go to terminal': ['terminal'],
                                    'go to duty free': ['duty free']}
        
        rospy.loginfo("Ready to receive voice commands")  
            
    def get_command(self, data):
        for (command, keywords) in self.keywords_to_command.iteritems():
            for word in keywords:
                if data.find(word) > -1:
                    return command
        
    def callback(self, msg):        
        command = self.get_command(msg.data)
        
        rospy.loginfo("Command: " + str(command))
        
        if command == 'go to terminal':    
            self.msg = "terminal"
        elif command == 'go to duty free':
            self.msg = "duty free"                
        else:
	    self.msg = "terminal"
            #return 
	    
	self.location_pub.publish(self.msg)

    def cleanup(self):
        pass

if __name__=="__main__":
    rospy.init_node('voice_nav')
    try:
        LocationRecogniser()
	rospy.spin()
    except:
        pass

