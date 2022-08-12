#include "ros/ros.h"
//#include "std_msgs/String.h"

#include "mars/IRStamped.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"


class ir_positions{
    private:
        ros::Subscriber sub;
        ros::Publisher pub;
        const float cov_x = 0.0025;

    public:
        ir_positions(ros::NodeHandle& n){
            sub =n.subscribe("ir_triggers",10,&ir_positions::conventer,this);
            pub = n.advertise<geometry_msgs::PoseWithCovarianceStamped>("ir_samples", 10);
        }
        ~ir_positions(){};


        void conventer(const mars::IRStamped::ConstPtr& msg){ 
            geometry_msgs::PoseWithCovarianceStamped arr; 
            arr.pose.covariance[0] = cov_x;
            switch(msg->beam_index){
                case 0:
                    ROS_INFO("[%d] position beam is received and converted", msg->beam_index);
                    arr.header =msg->header;
                    arr.pose.pose.position.x = 0.1;
                    pub.publish(arr);
                    break;
                case 1:
                    ROS_INFO(" [%d] position beam is received and converted", msg->beam_index);
                    arr.header =msg->header;
                    arr.pose.pose.position.x = 0.5;
                    pub.publish(arr);
                    break;
                case 2:
                    ROS_INFO("[%d] position beam is received and converted", msg->beam_index);
                    arr.header =msg->header;
                    arr.pose.pose.position.x = 1.8;
                    pub.publish(arr);
                    break;
                case 3:
                    ROS_INFO("[%d] position beam is received and converted", msg->beam_index);
                    arr.header =msg->header;
                    arr.pose.pose.position.x = 1.9;
                    pub.publish(arr);
                    break;
                default:
                    ROS_INFO("print something");
            }

        }
};




int main(int argc, char **argv){

    ros::init(argc,argv, "ir_positions");
    ros::NodeHandle n;
    ROS_INFO("ir positions node is ready");
    
    ir_positions ir_positions(n);
    ros::Rate loop_rate(10);

    ros::spin();

    return 0;
}