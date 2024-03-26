#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp" //导入消息接口

class TopicPublisher01 : public rclcpp::Node
{
public:
    // 构造函数,有一个参数为节点名称
    TopicPublisher01(std::string name) : Node(name)
    {
        RCLCPP_INFO(this->get_logger(), "%s节点已经启动.", name.c_str());

        // 创建发布者
        // 第一个参数话题名字为 command。第二个参数一般设置成10，即如果一次性有100条消息，默认保留最新的10个，其余的都扔掉。
        command_publisher_ = this->create_publisher<std_msgs::msg::String>("command", 10);

        // 创建定时器，500ms为周期，定时发布。chrono是c++ 11中的时间库，提供计时，时钟等功能。
        timer_ = this->create_wall_timer(std::chrono::milliseconds(500), std::bind(&TopicPublisher01::timer_callback, this));
    }

private:
    void timer_callback(){
        // 创建消息。std_msgs::msg::String是通过ROS2的消息文件自动生成的类，其原始消息文件内容可以通过命令行查询
        std_msgs::msg::String message;
        message.data = "forward";
        // 日志打印
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
        // 发布消息
        command_publisher_->publish(message);
    }


    // 声明话题发布者
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr command_publisher_;

    // 声名定时器指针，共享指针。定时器对应的类为rclcpp::TimerBase
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
    /* 1. 初始化rclcpp  */
    rclcpp::init(argc, argv);
    /* 2. 创建对应节点的共享指针对象,  产生一个topic_publisher_01的节点*/
    auto node = std::make_shared<TopicPublisher01>("topic_publisher_01_node");

    // 打印一句自我介绍
    RCLCPP_INFO(node->get_logger(), "topic_publisher_01_node发布者节点已经启动.");
    
    /* 3. 运行节点，并检测退出信号 Ctrl+C*/ 
    //保持节点运行，检测是否收到退出指令（Ctrl+C）
    rclcpp::spin(node);
    /* 4.停止运行,关闭rclcpp */
    rclcpp::shutdown();
    return 0;
}

