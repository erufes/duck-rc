#!/bin/bash

if [[ -f /opt/ros/$ROS_DISTRO/setup.bash ]]; then
    source /opt/ros/$ROS_DISTRO/setup.bash
fi

if [[ -f /opt/underlay_ws/install/setup.bash ]]; then
    source /opt/underlay_ws/install/setup.bash
fi

echo "all ok!"
ros2 launch ds4_driver ds4_twist.launch.xml
# tail -F /dev/null
# exec "$@"