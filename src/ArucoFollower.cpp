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

	TheMarkerSize = 0.05;
	TheCameraParameters.readFromXMLFile("../camera.yml");
        TheCameraParameters.resize(input_image_.size());
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
		ROS_INFO("Tx: %.4f, Ty: %.4f, Rz: %.4f", t_x_, t_y_, r_z_);
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

	input_image_ = cv_ptr->image;
	MDetector.detect(input_image_,TheMarkers,TheCameraParameters,TheMarkerSize);
	input_image_.copyTo(output_image_);
	for (unsigned int i=0;i<TheMarkers.size();i++) {
		if (TheMarkers[i].id == 805) {
			t_x_ = TheMarkers[i].Tvec.at<cv::Vec3f>(0,0)[0];
			t_y_ = TheMarkers[i].Tvec.at<cv::Vec3f>(0,0)[1];
			t_z_ = TheMarkers[i].Tvec.at<cv::Vec3f>(0,0)[2];

			r_x_ = TheMarkers[i].Rvec.at<cv::Vec3f>(0,0)[0];
			r_y_ = TheMarkers[i].Rvec.at<cv::Vec3f>(0,0)[1];
			r_z_ = TheMarkers[i].Rvec.at<cv::Vec3f>(0,0)[2];
		}
		TheMarkers[i].draw(output_image_,cv::Scalar(0,0,255), 1);
        }
	for (unsigned int i=0;i<TheMarkers.size();i++) {
            aruco::CvDrawingUtils::draw3dCube(output_image_,TheMarkers[i],TheCameraParameters);
            aruco::CvDrawingUtils::draw3dAxis(output_image_,TheMarkers[i],TheCameraParameters);
        }
	image_pub_.publish(cv_ptr->toImageMsg());
}
