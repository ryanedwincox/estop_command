// This is a ROS service that sends the software estop state to control computer

#include "ros/ros.h"
#include "estop_test/estopSignal.h"
#include <SerialStream.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <string>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "estop_control_client");

  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<estop_test::estopSignal>("estop_control");
  estop_test::estopSignal srv;

  while (ros::ok()) {
      srv.request.message = 3;
      if (client.call(srv))
      {
        ROS_INFO("Recieved handshake: %d", (bool)srv.response.handshake);
      }
      else
      {
        ROS_ERROR("Failed to call service estop_control");
        return 1;
      }

      ros::spinOnce();
  }
  client.shutdown();
  return 0;
}
