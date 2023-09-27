/*
 * ros_port.h
 *
 *  Created on: Sep 20, 2023
 *      Author: kch93
 */

#ifndef INC_ROS_PORT_H_
#define INC_ROS_PORT_H_

void laji_callback(const std_msgs::Int8 &msg);

void ros_setup(void);
void ros_loop(void);

#endif /* INC_ROS_PORT_H_ */
