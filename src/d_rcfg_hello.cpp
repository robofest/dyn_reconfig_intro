#include <ros/ros.h>
#include <string>
#include <dynamic_reconfigure/server.h>
#include <dyn_reconfig_intro/HelloConfig.h>  // package/cfg+"Config"

class HelloWithCFG {
  public:
    HelloWithCFG() {      
        server.setCallback(boost::bind(&HelloWithCFG::callback, this, _1, _2));
        while(ros::ok()) {
            ros::spinOnce();
            ros::Rate rate(freq);
            ROS_INFO_STREAM(msg);
            rate.sleep();
        }
    }
    ~HelloWithCFG() {}
    void callback(dyn_reconfig_intro::HelloConfig &config, uint32_t level);
    
  private:
    dynamic_reconfigure::Server<dyn_reconfig_intro::HelloConfig> server;
    double freq;
    std::string msg;
};

// called every time the Dynamic Reconfigure UI is updated by the user
void HelloWithCFG::callback(dyn_reconfig_intro::HelloConfig &config, uint32_t level) {
    freq = config.freq;
    msg = config.message;
    ROS_INFO_STREAM("Reconfigure Request: " << config.freq << " " << config.message);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "d_rcfg_hello");
  HelloWithCFG h{};
  ros::spin();
  return 0;
} // CJ
