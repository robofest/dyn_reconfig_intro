#include <ros/ros.h>
#include <string>
#include <dynamic_reconfigure/server.h>
#include <dyn_reconfig_intro/HelloConfig.h>  // package, cfg+"Config" appended

double freq;
std::string msg;

void callback(dyn_reconfig_intro::HelloConfig &config, uint32_t level) {
  freq = config.freq;
  msg = config.message;
  ROS_INFO_STREAM("Reconfigure Request: " << config.freq << " " << config.message);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "d_rcfg_hello");

  dynamic_reconfigure::Server<dyn_reconfig_intro::HelloConfig> server;
  dynamic_reconfigure::Server<dyn_reconfig_intro::HelloConfig>::CallbackType f;

  f = boost::bind(&callback, _1, _2);
  server.setCallback(f);

  while(ros::ok())
  {
    ros::spinOnce();
    ros::Rate rate(freq);
    ROS_INFO_STREAM(msg);
    rate.sleep();
  }
  return 0;
}
