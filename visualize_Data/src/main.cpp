#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include <object_msgs/CameraData.h>

using namespace std;

class VisualObject
{
public:
    VisualObject(ros::NodeHandle *nh);
    ~VisualObject() {};
    void cameraProc(const object_msgs::CameraData::ConstPtr&msg);
private:
    ros::NodeHandle* nh_;
    ros::Publisher camera_visual_pub;



};

VisualObject::VisualObject(ros::NodeHandle *nh)
{
    nh_ = nh;
    camera_visual_pub = nh_->advertise<visualization_msgs::MarkerArray>("/visual_camera",10);
}

void VisualObject::cameraProc(const object_msgs::CameraData::ConstPtr&msg)
{
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

    markerarry.markers.clear();
    for(int i=0;i<msg->objects.size();i++)
    {
        marker.id=i;
        marker.pose.position.x=msg->objects[i].pos_rel.x;
        marker.pose.position.y=msg->objects[i].pos_rel.y;
        marker.pose.position.z=0;
        markerarry.markers.push_back(marker);
    }

    camera_visual_pub.publish(markerarry);
    ROS_INFO("time is %ld",msg->timestamp);

}

void cameraCallback(const object_msgs::CameraData::ConstPtr &msg,
                    VisualObject *llc)
{
    llc->cameraProc(msg);
}



int main(int argc,char** argv)
{
    ros::init(argc,argv,"visual_node");
    ros::NodeHandle nh;
    VisualObject llc(&nh);
    ros::Subscriber camera_data_sub =nh.subscribe<object_msgs::CameraData>("/camera_data_topic",
                            10,boost::bind(cameraCallback,_1,&llc));
    ros::spin();
    return 0;
}

