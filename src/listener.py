#!/usr/bin/env python
import roslib; roslib.load_manifest('ChapticBelt')
import rospy
import bluetooth
from bluetooth import *
from ChapticBelt.msg import data


addr="00:06:66:42:21:78"
status=1

def callback(data, sock):
    angle=data.angle
    dista=data.range
    valid=ValidObstacle(dista, angle)
    if (valid==2):
	rospy.loginfo("VALID")
	vib=ChooseVibrator(angle)
	inten=round(CalcIntensity(dista), 7)	
	btdata = str(vib) + ";" + str(inten)
	SendBtData(btdata, sock)
	return 1    
    else:
	SendBtData("0", sock)
	rospy.loginfo("NOT VALID")
	return 1


def CheckForDevice():
    found=0
    a = bluetooth.discover_devices(4, True, False)
    for x in range(0, len(a)):    
        if found == 0:
            find=str(a[x])
            res = find.find(addr)
            if res == 0:
                found=1
            else:
                found=0
        else:
            break    
    return found


def SendBtData(data, sock):  
    try:
	rospy.loginfo(data)
	sock.send(data)
    except BluetoothError, e:
	rospy.loginfo("Bluetooth Error: %s" % e)
	#sock.close()
	sock.shutdown(2)
	listener()



def ConnectBelt(sock):
    if (CheckForDevice()==1):
        port = 1           
        try:        
	    status=sock.connect((addr, port))
	    rospy.loginfo("CONNECTED")	
        except BluetoothError, e:
	    rospy.loginfo("Bluetooth Error: %s" % e)
	    listener()
        return 1
    else:
        rospy.loginfo("Host Unreachable, Retrying...")
        rospy.sleep(5)
        ConnectBelt(sock)
    

def CalcIntensity(dista):
    value=dista*0.1
    return value


def ValidObstacle(dist, angle):    
    valid=0
    if (dist<20.0):
        valid+=1        
    if (angle>=0 and angle<=90) or (angle>=270 and angle<=360):
        valid+=1        
    return valid


def ChooseVibrator(angle):
    if (angle>=0 and angle<30):
        option=1        
    elif (angle>=30 and angle<60):
        option=2        
    elif (angle>=60 and angle<=90):
        option=3         
    elif (angle>=270 and angle<300):
        option=4        
    elif (angle>=300 and angle<330):
        option=5        
    elif (angle>=330 and angle<=360):
        option=6        
    else:
        option=0        
    return option


def listener():
    sock=bluetooth.BluetoothSocket( bluetooth.RFCOMM )
    #sock.settimeout(0)
    rospy.init_node('listener', anonymous=True)
    ConnectBelt(sock)
    rospy.Subscriber("SensorMsg", data, callback, sock)
    rospy.spin()
    


if __name__ == '__main__':
    listener()
