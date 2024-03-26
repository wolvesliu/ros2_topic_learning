#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp" //导入消息接口

class TopicSubscriber01  : public rclcpp::Node
{
public:
    // 构造函数,有一个参数为节点名称
    TopicSubscriber01(std::string name) : Node(name)
    {
        RCLCPP_INFO(this->get_logger(), "%s节点已经启动.", name.c_str());

        // 创建一个订阅者,订阅话题
        command_subscriber_ = this->create_subscription<std_msgs::msg::String>("command", 10, std::bind(&TopicSubscriber01::command_callback, this, std::placeholders::_1));
    }

private:
    // 声明一个订阅者
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr command_subscriber_;

    // 收到话题数据的回调函数
    void command_callback(const std_msgs::msg::String::SharedPtr msg)
    {
        double speed = 0.0f;
        if(msg->data == "forward")
        {
            speed = 0.2f;
        }
        RCLCPP_INFO(this->get_logger(), "收到[%s]指令，发送速度 %f", msg->data.c_str(),speed);
    }

};

int main(int argc, char **argv)
{
    /* 1. 初始化rclcpp  */
    rclcpp::init(argc, argv);
    /* 2. 创建对应节点的共享指针对象,  产生一个topic_publisher_01的节点*/
    auto node = std::make_shared<TopicSubscriber01>("topic_subscriber_01_node");

    // 打印一句自我介绍
    RCLCPP_INFO(node->get_logger(), "topic_subscriber_01_node订阅者节点已经启动.");
    
    /* 3. 运行节点，并检测退出信号 Ctrl+C*/ 
    //保持节点运行，检测是否收到退出指令（Ctrl+C）
    rclcpp::spin(node);
    /* 4.停止运行,关闭rclcpp */
    rclcpp::shutdown();
    return 0;
}

