/**
 *  ArucoFollower.cpp
 *
 *  Version: 0.0.0.0
 *  Created on: 08/06/2015
 *  Modified on: 08/06/2014
 *  Author: Adriano Henrique Rossette Leite (adrianohrl@gmail.com)
	    Alyson Pereira (alysonmp@gmail.com)
 *  Maintainer: Expertinos UNIFEI (expertinos.unifei@gmail.com)
 */

#include "br/edu/unifei/expertinos/aruco_follower/ArucoFollower.h"

using namespace br::edu::unifei::expertinos::aruco_follower;

/**
 *
 */
ArucoFollower::ArucoFollower() :
	it_(nh_) {
	nh_.param<int>("height", height_, 240); // in pixels
	nh_.param<int>("width", width_, 320); // in pixels
	image_sub_ = it_.subscribe("/camera/image_raw", 1, &ArucoFollower::imageCallback, this);

	image_pub_ = it_.advertise("/aruco_follower/output_video", 1);
	//imgRGB_ = cv::Mat(width_, height_, CV_8UC3, cv::Scalar::all(0));
	cv::namedWindow(ARUCO_FOLLOWER_WINDOW);
}

/**
 *
 */
ArucoFollower::~ArucoFollower() {
	image_sub_.shutdown();
	cv::destroyWindow(ARUCO_FOLLOWER_WINDOW);
}

/**
 *
 */
void ArucoFollower::spin() {
	ROS_INFO("Aruco Follower is up and running!!!");
	ros::Rate loop_rate(10.0);
	while (ros::ok()) {
		spinOnce();
		loop_rate.sleep();
	}
}

/**
 *
 */
void ArucoFollower::spinOnce() {
	ros::spinOnce();
}

/**
 *
 */
void ArucoFollower::imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
	cv_bridge::CvImagePtr cv_ptr;
	try
	{
		cv_ptr = cv_bridge::toCvCopy(msg);
	}
	catch (cv_bridge::Exception& e)
	{
		ROS_ERROR("cv_bridge exception: %s", e.what());
		return;
	} 

	imgRGB_ = cv_ptr->image;
	image_pub_.publish(cv_ptr->toImageMsg());
}
