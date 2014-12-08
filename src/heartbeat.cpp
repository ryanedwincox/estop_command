// Sends a heartbeat service at 10Hz

#include "ros/ros.h"
#include <cstdlib>
#include "std_srvs/Empty.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "heartbeat_client");

    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<std_srvs::Empty>("heartbeat");
    std_srvs::Empty srv;

    ros::Rate r(10); // 10Hz
    ros::Rate q(1); // Hz
    while(ros::ok())
    {
        if (client.call(srv))
        {
        ROS_INFO("alive");
        }
        else
        {
        ROS_ERROR("dead");
        q.sleep();
        }
        r.sleep();
    }
    client.shutdown();
    return 0;
}
