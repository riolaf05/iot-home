FROM arm32v7/ubuntu:16.04

MAINTAINER Rio<onslaught89@gmail.com>

RUN apt-get update && apt-get install -y --no-install-recommends \
    python3.5 \
    python3-pip \
    && \
apt-get clean && \
rm -rf /var/lib/apt/lists/*
RUN pip3 install paho-mqtt
RUN pip3 install urllib2
RUN pip3 install time

RUN mkdir /home/ubuntu/scripts

COPY MQTT_Client.py /home/ubuntu/scripts/

CMD [ "python3", "/home/ubuntu/scripts/MQTT_Client.py" ]