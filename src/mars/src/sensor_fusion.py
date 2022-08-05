#!/usr/bin/env python3
from cachetools import Cache
import rospy

from mars.msg import IRStamped

from geometry_msgs.msg import PoseWithCovarianceStamped, PoseStamped, TwistWithCovarianceStamped
from message_filters import Subscriber, Cache

class Sensor:
    def __init__(self):
        self.sub_r = rospy.Subscriber("radar_samples",TwistWithCovarianceStamped,self.radar)
        self.sub = rospy.Subscriber("ir_samples",PoseWithCovarianceStamped,self.sample_position)
        self.radar_sub = Subscriber("radar_samples",TwistWithCovarianceStamped)
        self.cache_ = Cache(self.radar_sub,1000)

    def sample_position(self,msg):
        print("oldest time: {}".format(self.cache_.getOldestTime()))
        print("latest time : {}".format(self.cache_.getLastestTime()))
        # res = TwistWithCovarianceStamped()
        # res.twist.twist.linear.x =  self.cache_.getElemBeforeTime(msg.header.stamp).twist.twist.linear.x
        # print("velocity: {}".format(res.twist.twist.linear.x))
    def radar(self,msg):
        print("Oldest time cached is: {}".format(msg))
        print("Oldest time cached is: {}".format(self.cache_.getOldestTime()))
        print("Last time received is : {}".format(self.cache_.getLastestTime()))

    # def radar_callback(self,msg):
    #     #print("I heard")
    #     #self.cache_.add(msg)
    #     #print("{}".format(self.cache_.getOldestTime))
    #     #print("{}".format(self.cache_.getLatestTime))
    #     pass





if __name__ == '__main__':
    rospy.init_node('sensor_fusion',anonymous=True)
    Sensor = Sensor()    
    print('sensor_fusion node is ready')
    rospy.spin()

