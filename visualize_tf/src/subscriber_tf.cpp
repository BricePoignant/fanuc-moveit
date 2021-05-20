#include<ros/ros.h>
#include<tf2_ros/transform_listener.h>
#include<geometry_msgs/TransformStamped.h>
int main(int argc, char** argv) {
    ros::init(argc, argv, "subscriber_tf");
    ros::NodeHandle nodeHandle;
    tf2_ros::Buffer tfBuffer;
    tf2_ros::TransformListener tfListener(tfBuffer);
    ros::Rate rate(10.0);while(nodeHandle.ok()) {
        try{
            geometry_msgs::TransformStamped tflange= tfBuffer.lookupTransform("flange","base_link", ros::Time(0));
            //(r, p, y) = tf2::transformations.euler_from_quaternion([tflange.transform.rotation.x, tflange.transform.rotation.y, tflange.transform.rotation.z, tflange.transform.rotation.w])
            ROS_INFO("Trans :[%f,%f,%f] ; Quat :[%f,%f,%f]", tflange.transform.translation.x, tflange.transform.translation.y, tflange.transform.translation.z, tflange.transform.rotation.x, tflange.transform.rotation.y, tflange.transform.rotation.z);
        } catch(tf2::TransformException&exception) {
            ROS_WARN("%s", exception.what());
            ros::Duration(1.0).sleep();
            continue;
        }
        rate.sleep();
    }return 0;
};