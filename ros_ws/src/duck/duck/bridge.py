import rclpy
import serial
import json
from rclpy.node import Node
from geometry_msgs.msg import TwistStamped
from datetime import datetime

class DS4Subscriber(Node):
    def __init__(self):
        super().__init__('DS4Subscriber')
        self._serial = serial.Serial('/dev/ttyACM0', baudrate=9600, write_timeout=1)
        self._subscription = self.create_subscription(
            TwistStamped, 'cmd_vel', self.listener_callback, qos_profile=10)
        self.get_logger().info('DS4 Bridge created successfully')
        self._lastTime = datetime.now()

    def listener_callback(self, msg: TwistStamped):
        controlObject = {'x': msg.twist.linear.y*2, 'y': msg.twist.linear.z/2}
        now = datetime.now()
        delta = now - self._lastTime
        if delta.microseconds < 100000:
            return
        self._lastTime = now

        self.get_logger().info(json.dumps(controlObject))
        try:
            if (self._serial.isOpen()):
                self._serial.write(json.dumps(controlObject).encode('ascii'))
            else:
                self.get_logger().info('[ERROR] Serial port is not open')
        except:
            self.get_logger().error('Timed out')

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
