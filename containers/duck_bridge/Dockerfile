FROM osrf/ros:humble-desktop

COPY ["entrypoint.sh", "/entrypoint.sh"]
RUN bash -c "chmod a+x /entrypoint.sh"


ENTRYPOINT [ "/entrypoint.sh" ]