#!/usr/bin/env python

import rospy
from geometry_msgs.msg import Twist
from turtlesim.msg import Pose
import math

class Turtle:
    def __init__(self):
        rospy.init_node("gotogoal")
        self.rate = rospy.Rate(10)

        self.pose = Pose()
        self.vel = Twist()
        self.goal_pose = Pose()

        self.velocity_publisher = rospy.Publisher("/turtle1/cmd_vel", Twist, queue_size= 10)
        self.pose_subscriber = rospy.Subscriber("/turtle1/cmd_vel", Pose, self.pose_callback)

    def pose_callback(self, data):
        self.pose.x = data.x
        self.pose.y = data.y
        self.pose.theta = data.theta
    
    def distance(self,pose,goal_pose):
        return math.sqrt((goal_pose.x - self.pose.x)**2 + (goal_pose.y - self.pose.y)**2)
    def angle(self,pose, goal_pose):
        return math.atan2(goal_pose.y - self.pose.y, goal_pose.x - self.pose.x)
    def goTo(self):
        self.goal_pose.x = float(input("Set your x goal: "))
        self.goal_pose.y = float(input("Set your y goal: "))

        while (self.angle(self.pose, self.goal_pose)- self.pose.theta) >= 0.05:
            self.vel.angular.z=1
            self.vel_pub.publish(self.vel)
        self.vel.angular.z = 0
        while self.distance(self.pose,self.goal_pose) >= 0.3:
            self.vel.linear.x = 1
            self.vel_pub.publish(self.vel)
            self.rate.sleep()
        self.vel.linear.x = 0
        self.vel_pub.publish(self.vel)
        rospy.logwarn("FUNCIONOU")
        rospy.loginfo("cheguei")
if __name__ == '__main__':
    turtle = Turtle()
    turtle.goTo()
    

