import rclpy
import serial
import json
from rclpy.node import Node
from geometry_msgs.msg import TwistStamped


class DS4Subscriber(Node):
    def __init__(self):
        super().__init__('DS4Subscriber')
        self._serial = serial.Serial('/dev/ttyACM0', baudrate=9600)
        self._subscription = self.create_subscription(
            TwistStamped, 'cmd_vel', self.listener_callback, qos_profile=10)
        self.get_logger().info('DS4 Bridge created successfully')

    def listener_callback(self, msg: TwistStamped):
        controlObject = {'x': msg.twist.linear.y, 'y': msg.twist.linear.z}
        self.get_logger().info(json.dumps(controlObject))
        self._serial.write(json.dumps(controlObject).encode('ascii'))

    def close_serial(self):
        self._serial.close()


def main():
    rclpy.init(args=None)
    sub = DS4Subscriber()
    rclpy.spin(sub)
    sub.close_serial()
    sub.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
