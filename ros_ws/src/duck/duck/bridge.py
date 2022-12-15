import rclpy
import serial
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
    ser = serial.Serial('/dev/ttyUSB0')
    print(ser.name)
    ser.write(b"HELLO!")
    rclpy.init(args=None)
    sub = DS4Subscriber()
    rclpy.spin(sub)
    sub.destroy_node()
    rclpy.shutdown()
    ser.close()


if __name__ == '__main__':
    main()
