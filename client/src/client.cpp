#include <ros/ros.h>
#include <client/time.h>
#include <client/show.h>
#include <ros/time.h>

int main(int argc, char** argv)
{
    // 初始化ROS节点
    ros::init(argc, argv, "client");

    // 创建节点句柄
    ros::NodeHandle n;

    // 发现/show_info服务后，创建一个服务客户端，连接名为/show_info的service
    ros::service::waitForService("/show_info");
    ros::ServiceClient client = n.serviceClient<client::show>("/show_info");

    // 初始化client::show的请求数据
    client::show srv;
    srv.request.request = "/client_topic";

    // 请求服务调用
    //ROS_INFO("Call service to show information.");
    client.call(srv);

    // 显示服务调用结果
    ROS_INFO("Topic received successfully.");

    // 创建一个Publisher，发布名为/client_topic的topic，消息类型为client::time，队列长度10
    ros::Publisher time_topic_pub = n.advertise<client::time>("/client_topic", 10);

    // 设置循环的频率
    ros::Rate loop_rate(1);

    while (ros::ok())
    {
        // 初始化client::time类型的消息
	ros::Time now = ros::Time::now();

    	client::time time_msg;

	time_msg.sec = now.toSec();
	time_msg.name = "/client_topic";

        // 发布消息
	time_topic_pub.publish(time_msg);

        // 按照循环频率延时
        loop_rate.sleep();
    }

	return 0;
};


