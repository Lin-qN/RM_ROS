#include <ros/ros.h>
#include <server/time.h>
#include <server/show.h>

// service回调函数，输入参数request，输出参数response
bool show_Callback(server::show::Request  &request,
         			server::show::Response &response)
{
    // 设置反馈数据
    response.response = request.request;
    ROS_INFO("%s", response.response.c_str());

    return true;
}

void time_Callback(const server::time::ConstPtr& time) {
    // 将接收到的消息打印出来
    ROS_INFO("Topic_name:%s   time:%lu   from:client",
             time->name.c_str(), time->sec);
}

int main(int argc, char **argv)
{
    // ROS节点初始化
    ros::init(argc, argv, "server");

    // 创建节点句柄
    ros::NodeHandle n;

    
    // 1.创建一个名为/show_info的server，注册回调函数show_Callback
    // 2.创建一个Subscriber，订阅名为client_topic的topic，注册回调函数time_Callback
    
    ros::ServiceServer service = n.advertiseService("/show_info", show_Callback);
    ros::Subscriber time_topic_sub = n.subscribe("/client_topic", 10, time_Callback);

    // 循环等待回调函数
    ROS_INFO("Ready to show informtion.");
    ros::spin();

    return 0;
}


