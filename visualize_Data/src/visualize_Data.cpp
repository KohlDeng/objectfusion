#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include <object_msgs/CameraData.h>



void callback(const object_msgs::CameraData::ConstPtr&msg)
{  ros::NodeHandle n;
    ros::Publisher visualization_pub=n.advertise<visualization_msgs::MarkerArray>("visualize",10);


    visualization_msgs::MarkerArray markerarry;
    visualization_msgs::Marker marker;

    marker.header.stamp=ros::Time::now();
    marker.header.frame_id="my_frame";

    marker.ns="namespace1";
    marker.type=visualization_msgs::Marker::CUBE;
    marker.action=visualization_msgs::Marker::ADD;
    marker.lifetime=ros::Duration();

    marker.scale.x=5;
    marker.scale.y=5;
    marker.scale.z=5;

    marker.color.r=1.0f;
    marker.color.g=0.0f;
    marker.color.b=0.0f;
    marker.color.a=1.0;

    marker.pose.orientation.x=0;
    marker.pose.orientation.y=0;
    marker.pose.orientation.z=0;
    marker.pose.orientation.w=1;
           

   

       for(int i=0;i<msg->objects.size();i++)
       {
           marker.id=i;
           
           marker.pose.position.x=msg->objects[i].pos_rel.x;
           marker.pose.position.y=msg->objects[i].pos_rel.y;
           marker.pose.position.z=0;
           
           markerarry.markers.push_back(marker);
       }


        visualization_pub.publish(markerarry);
        ROS_INFO("time is %ld",msg->timestamp);
        markerarry.markers.clear();
        
    }

int main(int argc,char** argv)
{
    ros::init(argc,argv,"CameraData_subscriber");
    ros::NodeHandle n;
    ros::Subscriber CameraData_sub=n.subscribe("camera_data_topic",10,callback);
    ros::spin();
    return 0;
}