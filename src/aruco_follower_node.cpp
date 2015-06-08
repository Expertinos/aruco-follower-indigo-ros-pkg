/**
 *  main.cpp
 *
 *  Version: 0.0.0.0
 *  Created on: 08/06/2015
 *  Modified on: 08/06/2015
 *  Author: Adriano Henrique Rossette Leite (adrianohrl@gmail.com)
	    Alyson Pereira (alysonmp@gmail.com)
 *  Maintainer: Expertinos UNIFEI (expertinos.unifei@gmail.com)
 */

#include "br/edu/unifei/expertinos/aruco_follower/ArucoFollower.h"

int main(int argc, char** argv) {
	ros::init(argc, argv, "aruco_follower_node");
	br::edu::unifei::expertinos::aruco_follower::ArucoFollower aruco_follower;
	aruco_follower.spin();
	return 0;
}
