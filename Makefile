bridge: bridge_deps
	docker exec -it duck_tools bash -c "source /ros_entrypoint.sh && cd /root/ros_ws && colcon build"

bridge_deps:
	docker exec -it duck_tools bash -c "source /ros_entrypoint.sh && cd /root/ros_ws && rosdep install -i --from-path src --rosdistro humble -y"