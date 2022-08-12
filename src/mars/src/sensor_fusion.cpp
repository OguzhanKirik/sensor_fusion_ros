#include "ros/ros.h"
#include "std_msgs/String.h"

#include "mars/IRStamped.h"
#include "geometry_msgs/TwistWithCovarianceStamped.h"
#include "geometry_msgs/PointStamped.h"
//#include "mars/convert_pose.h"
#include <cmath>

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
      ros::Publisher pub_position;
      geometry_msgs::PoseWithCovarianceStamped position_radar;
      geometry_msgs::PointStamped position_estimated;

      double time_new, time_intervall,time_last;
      int counter; 
      double radar_covariance;

      //  message_filters::Subscriber<geometry_msgs::TwistWithCovarianceStamped> radar_subs;
      //  message_filters::Cache<geometry_msgs::TwistWithCovarianceStamped> cache;
    public:
        Sensor(ros::NodeHandle& n){
            ROS_INFO("sensor fusion node is ready");
        
            sub_samples =n.subscribe("ir_samples",1000, &Sensor::sample_position,this);
            sub_radar =n.subscribe("radar_samples",1000, &Sensor::radar,this);
            pub_position = n.advertise<geometry_msgs::PointStamped>("estimated_position", 10);
            position_radar.pose.pose.position.x = 0;
            counter = 0;
            //sub_triggers = n.subscribe("ir_sammples",10,)
            //  radar_subs.subscribe(n,"radar_samples",1000);
            //  radar_subs.registerCallback(&Sensor::radar_callback,this);
            //  cache.setCacheSize(1000);    
        }
        ~Sensor(){};

        void sample_position(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg){
            position_estimated.header = msg->header;
  
            //this->radar_covariance = position_radar.pose.covariance[0];

            //measurement
            double diff = msg->pose.pose.position.x - position_radar.pose.pose.position.x;
            double Kalman_Gain  = position_radar.pose.covariance[0]/ (msg->pose.covariance[0]+position_radar.pose.covariance[0]);
            // Update
            position_estimated.point.x = msg->pose.pose.position.x + (Kalman_Gain * diff);
            //this->radar_covariance = (1 - Kalman_Gain) * position_radar.pose.covariance[0];


            //position_estimated.point.x = (position_radar.pose.pose.position.x *  position_radar.pose.covariance[0]) + (msg->pose.pose.position.x * msg->pose.covariance[0]);
            //position_estimated.point.x = (position_radar.pose.pose.position.x *  position_radar.pose.covariance[0]) + (msg->pose.pose.position.x * msg->pose.covariance[0]);
            std::cout  << "Position  predict:  "<< position_radar.pose.pose.position.x<< std::endl;    
            std::cout  << "Position  measurement:  "<< msg->pose.pose.position.x<< std::endl;     

            std::cout  << "Position  Update:  "<< position_estimated.point.x<< std::endl;     

            pub_position.publish(position_estimated);    
        }

        // void radar_callback(const geometry_msgs::TwistWithCovarianceStamped::ConstPtr& msg_radar){

        //       position_estimated.point.x = position_radar.pose.pose.position.x + msg_radar->twist.twist.linear.x;
        //       std::cout  << "Position  :  "<< position_estimated.point.x<< std::endl;          
        //     //arr.header = msg_radar->header;
        //     //cache.add(msg_radar);
        //     // std::cout << "Oldest time cached is " << cache.getOldestTime() << std::endl;
        //     // std::cout << "Last time received is " << cache.getLatestTime() << std::endl << std::endl;
        // }

          void radar(const geometry_msgs::TwistWithCovarianceStamped::ConstPtr& msg_radar){
              // Predict
            if(counter  == 0){
              this->time_last = msg_radar->header.stamp.toSec();
            }else{
              position_radar.header = msg_radar->header;
              position_radar.pose.covariance = msg_radar->twist.covariance;
              this->time_new = msg_radar->header.stamp.toSec();
              this->time_intervall = (this->time_new - this->time_last);
            // std::cout << "time_new  :: " << time_new << std::endl;
             //std::cout << "time intervall :: " << time_intervall << std::endl;
             // std::cout << " msg_radar->twist.twist.linear.x :: " << msg_radar->twist.twist.linear.x << std::endl;
              this->position_radar.pose.pose.position.x += ((msg_radar->twist.twist.linear.x * time_intervall)  );
              // std::cout  << "distance  :  "<< (msg_radar->twist.twist.linear.x * time_intervall) << std::endl;   
              // std::cout  << "Position  :  "<<  this->position_radar.pose.pose.position.x << std::endl;   
              this->time_last = this->time_new;  
               // std::cout << "time_last :: " << this->time_last << std::endl;
            }
            counter++;
            //  std::cout << "radar vel " << msg_radar->twist.twist.linear.x <<  std::endl;
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