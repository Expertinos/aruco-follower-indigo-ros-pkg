/**
 *  ArucoFollower.h
 *
 *  Version: 0.0.0.0
 *  Created on: 08/06/2015
 *  Modified on: 08/06/2015
 *  Author: Adriano Henrique Rossette Leite (adrianohrl@gmail.com)
	    Alyson Pereira (alysonmp@gmail.com)
 *  Maintainer: Expertinos UNIFEI (expertinos.unifei@gmail.com)
 */

#ifndef ARUCO_FOLLOWER_H_
#define ARUCO_FOLLOWER_H_

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define ARUCO_FOLLOWER_WINDOW "Aruco Follower Window"

namespace br {

	namespace edu {

		namespace unifei {

			namespace expertinos {

				namespace aruco_follower {

					class ArucoFollower {

					public:

						ArucoFollower();
						~ArucoFollower();

						void spin();
						void spinOnce();

					private:

						ros::NodeHandle nh_;

						image_transport::ImageTransport it_;
						image_transport::Subscriber image_sub_;
						image_transport::Publisher image_pub_;

						cv::Mat imgRGB_;
						int width_, height_;

						void imageCallback(const sensor_msgs::ImageConstPtr& msg);

					};
			
				}

			}

		}

	}

}

#endif /* ARUCO_FOLLOWER_H_ */
