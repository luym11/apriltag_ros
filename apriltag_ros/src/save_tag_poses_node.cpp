#include <ros/ros.h>
#include <apriltag_ros/AprilTagDetectionArray.h>
#include <tf/transform_listener.h>
#include <fstream>

#include <apriltag_ros/SaveTagPoses.hpp>

SaveTagPoses* pSaveTagPoses0 = NULL;

void msg_callback(const apriltag_ros::AprilTagDetectionArray::ConstPtr &msg)
{
	apriltag_ros::AprilTagDetection detection;
	int id;
	geometry_msgs::PoseStamped pose;
	tf::StampedTransform transform;
	tf::Quaternion rot;
	float x, y, z;
	float rx, ry, rz, rw;
	for(size_t i = 0; i < msg->detections.size(); i++)
	{

		detection = msg->detections[i];
		id = detection.id[0];

		try
		{
			pSaveTagPoses0->listener.lookupTransform("/camera_odom_frame", "tag_"+std::to_string(id), ros::Time(0), transform);
		}
		catch(tf::TransformException ex)
		{
			ROS_ERROR("%s",ex.what());
		}

		rot = transform.getRotation();
		x = transform.getOrigin().x();
		y = transform.getOrigin().y();
		z = transform.getOrigin().z();
		rx = rot.x();
		ry = rot.y();
		rz = rot.z();
		rw = rot.w();

		ROS_INFO("Tag ID: %d  position: %f %f %f  Rotation: %f %f %f",id, x, y, z, rx, ry, rz);
	}
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "save_tag_poses_node");
	ros::NodeHandle nh;

	ROS_INFO("Starting save_tag_poses node..");

    pSaveTagPoses0 = new (SaveTagPoses);

	ros::Subscriber sub = nh.subscribe("/tag_detections", 1000, msg_callback);
	ros::Rate r(100);
	while(ros::ok()){
		ros::spinOnce();
		r.sleep();
	}
	return 0;
}
