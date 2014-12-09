// This is a ROS service that sends the software estop state to control computer

#include "ros/ros.h"
#include "estop_command/estopSignal.h"
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <string>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "estop_control_client");

    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<estop_command::estopSignal>("estop_control");
    estop_command::estopSignal srv;

    int message = 1;
    n.getParam("/msg", message);

    ros::Rate r(1); // 1Hz
    while (ros::ok()) {
        srv.request.message = message;
        if (client.call(srv))  // wait for response
        {
            ROS_INFO("Recieved handshake: %d", (bool)srv.response.handshake);
        }
        else
        {
            ROS_ERROR("Failed to call service estop_control");
            r.sleep();
        }
    }
    client.shutdown();
    return 0;
}
