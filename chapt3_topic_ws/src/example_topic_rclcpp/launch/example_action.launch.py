# 导入库
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    """launch内容描述函数，由ros2 launch 扫描调用"""

    topic_publisher_01_node = Node(
        package="example_topic_rclcpp",#节点所在的功能包
        executable="topic_publisher_01_node"#表示要运行的可执行文件名或脚本名字.py   就是节点
    )

    topic_subscriber_01_node = Node(
        package="example_topic_rclcpp",
        executable="topic_subscriber_01_node"
    )

    # 创建LaunchDescription对象launch_description,用于描述launch文件
    launch_description = LaunchDescription(
        [topic_publisher_01_node, topic_subscriber_01_node])
    
    # 返回让ROS2根据launch描述执行节点
    return launch_description
