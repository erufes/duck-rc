FROM osrf/ros:humble-desktop

WORKDIR /tmp

RUN bash -c "python3 <(curl https://bootstrap.pypa.io/get-pip.py)"
RUN bash -c "pip install pyserial --no-cache-dir"

WORKDIR /
COPY ["entrypoint.sh", "/entrypoint.sh"]
RUN bash -c "chmod a+x /entrypoint.sh"


ENTRYPOINT [ "/entrypoint.sh" ]