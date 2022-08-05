#include "ros/ros.h"
#include "std_msgs/String.h"

#include "mars/IRStamped.h"
#include "geometry_msgs/TwistWithCovarianceStamped.h"
#include "geometry_msgs/PointStamped.h"
//#include "mars/convert_pose.h"

#include <message_filters/subscriber.h>
#include <message_filters/cache.h>
#include "geometry_msgs/PoseWithCovarianceStamped.h"

//#include <message_filters/time_synchronizer.h>
#include <ros/console.h>


//geometry_msgs::PointStamped arr;
//message_filters::Cache<geometry_msgs::TwistWithCovarianceStamped> cache;

 class Sensor{
    private:
      ros::Subscriber sub_radar;
      ros::Subscriber sub_samples;

      // message_filters::Subscriber<geometry_msgs::TwistWithCovarianceStamped> radar_subs;
      // message_filters::Cache<geometry_msgs::TwistWithCovarianceStamped> cache;
      geometry_msgs::PointStamped current_position;


    public:
        Sensor(ros::NodeHandle& n){
            ROS_INFO("sensor fusion node is ready");
        
            sub_samples =n.subscribe("ir_samples",1000, &Sensor::sample_position,this);
            sub_radar =n.subscribe("radar_samples",1000, &Sensor::radar,this);
            //sub_triggers = n.subscribe("ir_sammples",10,)
            // radar_subs.subscribe(n,"radar_samples",1000);
            // radar_subs.registerCallback(&Sensor::radar_callback,this);
            // cache.setCacheSize(1000);    
        }
        ~Sensor(){};

        void sample_position(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg){
          // arr.header = msg->header;
          // arr.point.x = msg->pose.pose.position.x;


           std::cout  << "I heard header  :  "<<msg->pose.pose.position.x << std::endl;
          //  std::cout << "velocity: "<<cache.getElemBeforeTime(msg->header.stamp)->twist   << std::endl;
          
        }
        void radar_callback(const geometry_msgs::TwistWithCovarianceStamped::ConstPtr& msg_radar){
            //arr.header = msg_radar->header;
            //cache.add(msg_radar);
            // std::cout << "Oldest time cached is " << cache.getOldestTime() << std::endl;
            // std::cout << "Last time received is " << cache.getLatestTime() << std::endl << std::endl;
        }

          void radar(const geometry_msgs::TwistWithCovarianceStamped::ConstPtr& msg_radar){
            
             //std::cout << "radar vel " << msg_radar->twist.twist.linear.x <<  std::endl;
            // std::cout << "Last time received is " << cache.getLatestTime() << std::endl << std::endl;
        }

        

};



int main(int argc, char **argv){

    ros::init(argc,argv, "sensor_fusion");
    ros::NodeHandle n;
    Sensor sensor(n);    
    ros::spin();
  
    return 0;
}