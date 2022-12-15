#!/bin/bash

source /ros_entrypoint.sh
source /root/ros_ws/install/setup.sh

# ros2 launch ds4_driver ds4_twist.launch.xml
tail -F /dev/null
# ros2 run duck bridge
# exec "$@"