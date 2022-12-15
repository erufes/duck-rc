import rclpy
from rclpy.node import Node
from geometry_msgs.msg import TwistStamped


class DS4Subscriber(Node):
    def __init__(self):
        super().__init__('DS4Subscriber')
        self._subscription = self.create_subscription(
            TwistStamped, 'cmd_vel', self.listener_callback, qos_profile=10)
        self.get_logger().info('DS4 Bridge created successfully')

    def listener_callback(self, msg: TwistStamped):
        self.get_logger().info('Got: %s' % msg.twist.linear)


def main():
    print("Hi from bridge")
    rclpy.init(args=None)
    print("Creating sub...")
    sub = DS4Subscriber()
    rclpy.spin(sub)
    sub.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
