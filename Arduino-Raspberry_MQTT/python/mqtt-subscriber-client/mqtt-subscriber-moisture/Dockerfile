FROM arm32v7/ubuntu:16.04

MAINTAINER Rio<onslaught89@gmail.com>

RUN apt-get update \
    && apt-get upgrade -y \
    && apt-get install -y \
    build-essential \
    ca-certificates \
    gcc \
    git \
    libpq-dev \
    make \
    python-pip \
    python2.7 \
    python2.7-dev \
    ssh \
    && apt-get autoremove \
    && apt-get clean

RUN pip install paho-mqtt

RUN mkdir $HOME/scripts

COPY MQTT_Client.py /home/root/scripts/

COPY ./on_messages.py /home/root/scripts/

CMD [ "python", "/home/root/scripts/MQTT_Client.py" ]

